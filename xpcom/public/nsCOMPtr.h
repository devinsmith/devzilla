/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * The contents of this file are subject to the Netscape Public License
 * Version 1.0 (the "NPL"); you may not use this file except in
 * compliance with the NPL.  You may obtain a copy of the NPL at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the NPL is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the NPL
 * for the specific language governing rights and limitations under the
 * NPL.
 *
 * The Initial Developer of this code under the NPL is Netscape
 * Communications Corporation.  Portions created by Netscape are
 * Copyright (C) 1998 Netscape Communications Corporation.  All Rights
 * Reserved.
 */

#ifndef nsCOMPtr_h___
#define nsCOMPtr_h___



  // Wrapping includes can speed up compiles (see "Large Scale C++ Software Design")
#ifndef nsDebug_h___
  #include "nsDebug.h"
    // for |NS_PRECONDITION|
#endif

#ifndef nsISupports_h___
  #include "nsISupports.h"
    // for |nsresult|, |NS_ADDREF|, et al
#endif

/*
	Having problems?
	
  See the User Manual at:
    <http://www.meer.net/ScottCollins/doc/nsCOMPtr.html>, or
    <http://www.mozilla.org/projects/xpcom/nsCOMPtr.html>

  What is |nsCOMPtr|?

    |nsCOMPtr| is a `smart-pointer'.  It is a template class that acts, syntactically,
    just like an ordinary pointer in C or C++, i.e., you can apply |*| or |->| to it to
    `get to' what it points at.  |nsCOMPtr| is smart in that, unlike a raw COM
    interface pointer, |nsCOMPtr| manages |AddRef|, |Release|, and |QueryInterface|
    _for_ you.

    For instance, here is a typical snippet of code (at its most compact) where you assign
    a COM interface pointer into a member variable:

      NS_IF_RELEASE(mFoop);  // If I have one already, I must release it before over-writing it.
      if ( mFooP = aPtr )    // Now it's safe to assign it in, and, if it's not NULL
        mFooP->AddRef();     // I must |AddRef| it, since I'll be holding on to it.

    If our member variable |mFooP| were a |nsCOMPtr|, however, the snippet above
    would look like this:

      mFoop = aPtr;        // Note: automatically |Release|s the old and |AddRef|s the new

    |nsCOMPtr| helps you write code that is leak-proof, exception safe, and significantly
    less verbose than you would with raw COM interface pointers.  With |nsCOMPtr|, you
    may never have to call |AddRef|, |Release|, or |QueryInterface| by hand.


    You still have to understand COM.  You still have to know which functions return
    interface pointers that have already been |AddRef|ed and which don't.  You still
    have to ensure your program logic doesn't produce circularly referencing garbage.
    |nsCOMPtr| is not a panacea.  It is, however, helpful, easy to use, well-tested,
    and polite.  It doesn't require that a function author cooperate with you, nor does
    your use force others to use it.


  Where should I use |nsCOMPtr|?

    ...


  Where _shouldn't_ I use |nsCOMPtr|?

    In public interfaces... [[others]]


  How does a |nsCOMPtr| differ from a raw pointer?

    A |nsCOMPtr| differs, syntactically, from a raw COM interface pointer in three
    ways:

      + It's declared differently, e.g.,

        // instead of saying                // you say
        IFoo* fooP;                         nsCOMPtr<IFoo> fooP;


      + You can't call |AddRef| or |Release| through it,

        fooP->AddRef();   // OK             fooP->AddRef();   // Error: no permission
        fooP->Release();  // OK             fooP->Release();  // Error: no permission


      + You can't just apply an |&| to it to pass it to the typical `getter' function

        AcquireFoo(&fooP);                  AcquireFoo( getter_AddRefs(fooP) );
        GetFoo(&fooP);                      GetFoo( getter_doesnt_AddRef(fooP) );


  How do I use |nsCOMPtr|?

    Typically, you can use a |nsCOMPtr| exactly as you would a standard COM
    interface pointer:

      IFoo* fooP;                           nsCOMPtr<IFoo> fooP;
      // ...                                // ...
      fooP->SomeFunction(x, y, z);          fooP->SomeFunction(x, y, z);
      AnotherFunction(fooP);                AnotherFunction(fooP);

      if ( fooP )                           if ( fooP )
        // ...                                // ...

      if ( fooP == barP )                   if ( fooP == barP )
        // ...                                // ...

    There are some differences, though.  In particular, you can't call |AddRef| or |Release|
    through a |nsCOMPtr| directly, nor would you need to.  |AddRef| is called for you
    whenever you assign a COM interface pointer _into_ a |nsCOMPtr|.  |Release| is
    called on the old value, and also when the |nsCOMPtr| goes out of scope.  Trying
    to call |AddRef| or |Release| yourself will generate a compile-time error.

      fooP->AddRef();                       // fooP->AddRef();  // ERROR: no permission
      fooP->Release();                      // fooP->Release(); // ERROR: no permission

    The final difference is that a bare |nsCOMPtr| (or rather a pointer to it) can't
    be supplied as an argument to a function that `fills in' a COM interface pointer.
    Rather it must be wrapped with a utility call that says whether the function calls
    |AddRef| before returning, e.g.,

      ...->QueryInterface(riid, &fooP)      ...->QueryInterface(riid, getter_AddRefs(fooP))

      LookupFoo(&fooP);                     LookupFoo( getter_doesnt_AddRef(fooP) );

    Don't worry.  It's a compile-time error if you forget to wrap it.

		Compare the raw-pointer way...

      IFoo* foo = 0;
      nsresult status = CreateIFoo(&foo);
      if ( NS_SUCCEEDED(status) )
        {
          IBar* bar = 0;
          if ( NS_SUCCEEDED(status = foo->QueryInterface(riid, &bar)) )
            {
              IFooBar* foobar = 0;
              if ( NS_SUCCEEDED(status = CreateIFooBar(foo, bar, &foobar)) )
                {
                  foobar->DoTheReallyHardThing();
                  foobar->Release();
                }
              bar->Release();
            }
          foo->Release();
        }



		To the smart-pointer way...

			nsCOMPtr<IFoo> fooP;
			nsresult status = CreateIFoo( getter_AddRefs(fooP) );
			if ( NS_SUCCEEDED(status) )
				if ( nsCOMPtr<IBar> barP( fooP ) )
					{
						nsCOMPtr<IFooBar> fooBarP;
						if ( NS_SUCCEEDED(status = CreateIFooBar(fooP, barP, getter_AddRefs(fooBarP))) )
							fooBarP->DoTheReallyHardThing();
					}

    
  Is there an easy way to convert my current code?

    ...


  What do I have to beware of?

    VC++ < 6.0 _can't_ handle the following situation

      class nsIFoo;          // forward declare some class
      // ...
      nsCOMPtr<nsIFoo> bar;  // ERROR: incomplete type nsIFoo, etc.
 
    Instead, you must make sure that you actually defined the underlying interface class, e.g.,

      #include "nsIFoo.h"    // fully defines |class nsIFoo|
      // ...
      nsCOMPtr<nsIFoo> bar;  // no problem

    Why is this?  It's because VC++ tries to instantiate every member of the template
    as soon as it sees the template declarations.  Bad compiler.  No cookie!
    [[Thanks to mjudge, waterson, and pinkerton on this one.]]


  Why does |getter_AddRefs| have such a funny name?  I.e., why doesn't it follow our
  naming conventions?

    |getter_AddRefs| and |getter_doesnt_AddRef| use underscores for the same
    reason our special macros do, quoting from our coding conventions "...to make them
    stick out like a sore thumb".  Note also that since |AddRef| is one word,
    |getter_AddRefs| and |getter_doesnt_AddRef| couldn't have the right spacing if only inter-
    caps were used. 
*/




/*
  TO DO...
  
  	+ make StartAssignment optionally inlined
    + make constructor for |nsQueryInterface| explicit (suddenly construct/assign from raw pointer becomes illegal)
    + Improve internal documentation
      + mention *&
      + alternatives for comparison
      + do_QueryInterface
*/

/*
  WARNING:
    This file defines several macros for internal use only.  These macros begin with the
    prefix |NSCAP_|.  Do not use these macros in your own code.  They are for internal use
    only for cross-platform compatibility, and are subject to change without notice.
*/


  /*
    Set up some |#define|s to turn off a couple of troublesome C++ features.
    Interestingly, none of the compilers barf on template stuff.  These are set up automatically
    by the autoconf system for all Unixes.  (Temporarily, I hope) I have to define them
    myself for Mac and Windows.
  */

	// under Metrowerks (Mac), we don't have autoconf yet
#ifdef __MWERKS__
	#define HAVE_CPP_USING
	#define HAVE_CPP_EXPLICIT
	#define HAVE_CPP_NEW_CASTS
#endif

	// under VC++ (Windows), we don't have autoconf yet
#ifdef _MSC_VER
	#define HAVE_CPP_EXPLICIT
	#define HAVE_CPP_USING
	#define HAVE_CPP_NEW_CASTS

  #if (_MSC_VER<1100)
		  // before 5.0, VC++ couldn't handle explicit
    #undef HAVE_CPP_EXPLICIT
  #elif (_MSC_VER==1100)
      // VC++5.0 has an internal compiler error (sometimes) without this
    #undef HAVE_CPP_USING
  #endif
#endif


	/*
		If the compiler doesn't support |explicit|, we'll just make it go away, trusting
		that the builds under compilers that do have it will keep us on the straight and narrow.
	*/
#ifndef HAVE_CPP_EXPLICIT
  #define explicit
#endif

#ifdef HAVE_CPP_NEW_CASTS
	#define NSCAP_REINTERPRET_CAST(T,x)	reinterpret_cast<T>(x)
#else
	#define NSCAP_REINTERPRET_CAST(T,x) ((T)(x))
#endif

#ifdef NSCAP_FEATURE_DEBUG_MACROS
  #define NSCAP_ADDREF(ptr)    NS_ADDREF(ptr)
  #define NSCAP_RELEASE(ptr)   NS_RELEASE(ptr)
#else
  #define NSCAP_ADDREF(ptr)    (ptr)->AddRef()
  #define NSCAP_RELEASE(ptr)   (ptr)->Release()
#endif

  /*
    WARNING:
      VC++4.2 is very picky.  To compile under VC++4.2, the classes must be defined
      in an order that satisfies:
    
        nsDerivedSafe < nsCOMPtr
        nsDontAddRef < nsCOMPtr
        nsCOMPtr < nsGetterAddRefs

      The other compilers probably won't complain, so please don't reorder these
      classes, on pain of breaking 4.2 compatibility.
  */


template <class T>
class nsDerivedSafe : public T
    /*
      No client should ever see or have to type the name of this class.  It is the
      artifact that makes it a compile-time error to call |AddRef| and |Release|
      on a |nsCOMPtr|.

      See |nsCOMPtr::operator->|, |nsCOMPtr::operator*|, et al.
    */
  {
    private:
#ifdef HAVE_CPP_USING
      using T::AddRef;
      using T::Release;
#else
      NS_IMETHOD_(nsrefcnt) AddRef(void);
      NS_IMETHOD_(nsrefcnt) Release(void);
#endif

      void operator delete( void*, size_t );                  // NOT TO BE IMPLEMENTED
        // declaring |operator delete| private makes calling delete on an interface pointer a compile error

      nsDerivedSafe<T>& operator=( const nsDerivedSafe<T>& ); // NOT TO BE IMPLEMENTED
        // you may not call |operator=()| through a dereferenced |nsCOMPtr|, because you'd get the wrong one
  };

#if !defined(HAVE_CPP_USING) && defined(NEED_CPP_UNUSED_IMPLEMENTATIONS)
template <class T>
nsrefcnt
nsDerivedSafe<T>::AddRef()
  {
    return 0;
  }

template <class T>
nsrefcnt
nsDerivedSafe<T>::Release()
  {
    return 0;
  }

#endif




template <class T>
struct nsDontQueryInterface
    /*
      ...
    */
  {
    explicit
    nsDontQueryInterface( T* aRawPtr )
        : mRawPtr(aRawPtr)
      {
        // nothing else to do here
      }

    T* mRawPtr;
  };

template <class T>
inline
nsDontQueryInterface<T>
dont_QueryInterface( T* aRawPtr )
  {
    return nsDontQueryInterface<T>(aRawPtr);
  }




struct nsQueryInterface
  {
    explicit
    nsQueryInterface( nsISupports* aRawPtr, nsresult* error = 0 )
        : mRawPtr(aRawPtr),
          mErrorPtr(error)
      {
        // nothing else to do here
      }

    nsISupports* mRawPtr;
    nsresult*    mErrorPtr;
  };

inline
nsQueryInterface
do_QueryInterface( nsISupports* aRawPtr, nsresult* error = 0 )
  {
    return nsQueryInterface(aRawPtr, error);
  }




template <class T>
struct nsDontAddRef
    /*
      ...cooperates with |nsCOMPtr| to allow you to assign in a pointer _without_
      |AddRef|ing it.  You would rarely use this directly, but rather through the
      machinery of |getter_AddRefs| in the argument list to functions that |AddRef|
      their results before returning them to the caller.

      See also |getter_AddRefs()| and |class nsGetterAddRefs|.
    */
  {
    explicit
    nsDontAddRef( T* aRawPtr )
        : mRawPtr(aRawPtr)
      {
        // nothing else to do here
      }

    T* mRawPtr;
  };

	// This call is now deprecated.  Use |getter_AddRefs()| instead.
template <class T>
inline
nsDontAddRef<T>
dont_AddRef( T* aRawPtr )
    /*
      ...makes typing easier, because it deduces the template type, e.g., 
      you write |dont_AddRef(fooP)| instead of |nsDontAddRef<IFoo>(fooP)|.
    */
  {
    return nsDontAddRef<T>(aRawPtr);
  }

template <class T>
inline
nsDontAddRef<T>
getter_AddRefs( T* aRawPtr )
	{
		return nsDontAddRef<T>(aRawPtr);
	}



class nsCOMPtr_base
  {
    public:

      nsCOMPtr_base( nsISupports* rawPtr = 0 )
          : mRawPtr(rawPtr)
        {
          // nothing else to do here
        }

     ~nsCOMPtr_base()
        {
          if ( mRawPtr )
            NSCAP_RELEASE(mRawPtr);
        }

      NS_EXPORT void    assign_with_AddRef( nsISupports* );
      NS_EXPORT void    assign_with_QueryInterface( nsISupports*, const nsIID&, nsresult* );
      NS_EXPORT void**  begin_assignment();

    protected:
      nsISupports* mRawPtr;
  };



template <class T>
class nsCOMPtr : private nsCOMPtr_base
    /*
      ...
    */
  {
    public:
      typedef T element_type;

      nsCOMPtr()
          // : nsCOMPtr_base(0)
        {
          // nothing else to do here
        }

      nsCOMPtr( const nsQueryInterface& aSmartPtr )
          // : nsCOMPtr_base(0)
        {
          assign_with_QueryInterface(aSmartPtr.mRawPtr, T::GetIID(), aSmartPtr.mErrorPtr);
        }

      nsCOMPtr( const nsDontAddRef<T>& aSmartPtr )
          : nsCOMPtr_base(aSmartPtr.mRawPtr)
        {
          // nothing else to do here
        }

      nsCOMPtr( const nsDontQueryInterface<T>& aSmartPtr )
          : nsCOMPtr_base(aSmartPtr.mRawPtr)
        {
          if ( mRawPtr )
            NSCAP_ADDREF(mRawPtr);
        }

      nsCOMPtr( const nsCOMPtr<T>& aSmartPtr )
          : nsCOMPtr_base(aSmartPtr.mRawPtr)
        {
          if ( mRawPtr )
            NSCAP_ADDREF(mRawPtr);
        }

      nsCOMPtr<T>&
      operator=( const nsQueryInterface& rhs )
        {
          assign_with_QueryInterface(rhs.mRawPtr, T::GetIID(), rhs.mErrorPtr);
          return *this;
        }

      nsCOMPtr<T>&
      operator=( const nsDontAddRef<T>& rhs )
        {
          if ( mRawPtr )
            NSCAP_RELEASE(mRawPtr);
          mRawPtr = rhs.mRawPtr;
          return *this;
        }

      nsCOMPtr<T>&
      operator=( const nsDontQueryInterface<T>& rhs )
        {
          assign_with_AddRef(rhs.mRawPtr);
          return *this;
        }

      nsCOMPtr<T>&
      operator=( const nsCOMPtr<T>& rhs )
        {
          assign_with_AddRef(rhs.mRawPtr);
          return *this;
        }

      nsDerivedSafe<T>*
      get() const
          // returns a |nsDerivedSafe<T>*| to deny clients the use of |AddRef| and |Release|
        {
          return NSCAP_REINTERPRET_CAST(nsDerivedSafe<T>*, mRawPtr);
        }

      nsDerivedSafe<T>*
      operator->() const
          // returns a |nsDerivedSafe<T>*| to deny clients the use of |AddRef| and |Release|
        {
          NS_PRECONDITION(mRawPtr != 0, "You can't dereference a NULL nsCOMPtr with operator->().");
          return get();
        }

      nsDerivedSafe<T>&
      operator*() const
          // returns a |nsDerivedSafe<T>*| to deny clients the use of |AddRef| and |Release|
        {
          NS_PRECONDITION(mRawPtr != 0, "You can't dereference a NULL nsCOMPtr with operator*().");
          return *get();
        }

      operator nsDerivedSafe<T>*() const
        {
          return get();
        }

#if 0
    private:
      friend class nsGetterAddRefs<T>;

      /*
        In a perfect world, the following member function, |StartAssignment|, would be private.
        It is and should be only accessed by the closely related class |nsGetterAddRefs<T>|.

        Unfortunately, some compilers---most notably VC++5.0---fail to grok the
        friend declaration above or in any alternate acceptable form.  So, physically
        it will be public (until our compilers get smarter); but it is not to be
        considered part of the logical public interface.
      */
#endif

      T**
      StartAssignment()
        {
          return NSCAP_REINTERPRET_CAST(T**, begin_assignment());
        }
  };


template <class T>
class nsGetterAddRefs
    /*
      ...

      This class is designed to be used for anonymous temporary objects in the
      argument list of calls that return COM interface pointers, e.g.,

        nsCOMPtr<IFoo> fooP;
        ...->QueryInterface(iid, nsGetterAddRefs<IFoo>(fooP))
        ...->QueryInterface(iid, getter_AddRefs(fooP))

      When initialized with a |nsCOMPtr|, as in the example above, it returns
      a |void**| (or |T**| if needed) that the outer call (|QueryInterface| in this
      case) can fill in.
    */
  {
    public:
      explicit
      nsGetterAddRefs( nsCOMPtr<T>& aSmartPtr )
          : mTargetSmartPtr(aSmartPtr)
        {
          // nothing else to do
        }

      operator void**()
        {
          // NS_PRECONDITION(mTargetSmartPtr != 0, "getter_AddRefs into no destination");
          return NSCAP_REINTERPRET_CAST(void**, mTargetSmartPtr.StartAssignment());
        }

      T*&
      operator*()
        {
          // NS_PRECONDITION(mTargetSmartPtr != 0, "getter_AddRefs into no destination");
          return *(mTargetSmartPtr.StartAssignment());
        }

      operator T**()
        {
          // NS_PRECONDITION(mTargetSmartPtr != 0, "getter_AddRefs into no destination");
          return mTargetSmartPtr.StartAssignment();
        }

    private:
      nsCOMPtr<T>& mTargetSmartPtr;
  };

template <class T>
inline
nsGetterAddRefs<T>
getter_AddRefs( nsCOMPtr<T>& aSmartPtr )
    /*
      Used around a |nsCOMPtr| when 
      ...makes the class |nsGetterAddRefs<T>| invisible.
    */
  {
    return nsGetterAddRefs<T>(aSmartPtr);
  }




#endif // !defined(nsCOMPtr_h___)
