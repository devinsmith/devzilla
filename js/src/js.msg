/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
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

/*
	This is the JavaScript error message file.

	The format for each JS error message is:

MSG_DEF(<SYMBOLIC_NAME>, <ERROR_NUMBER>, <ARGUMENT_COUNT>, <EXCEPTION_NAME>,
	<FORMAT_STRING>)

	where ;
	<SYMBOLIC_NAME> is a legal C identifer that will be used in the
	JS engine source.

	<ERROR_NUMBER> is an unique integral value identifying this error.

	<ARGUMENT_COUNT> is an integer literal specifying the total number of
	replaceable arguments in the following format string.

	<EXCEPTION_NAME> is an exception index from the enum in jsexn.c;
	JSEXN_NONE for none.  The given exception index will be raised by the
	engine when the corresponding error occurs.

	<FORMAT_STRING> is a string literal, optionally containing sequences
	{X} where X  is an integer representing the argument number that will
	be replaced with a string value when the error is reported.

	e.g.

	MSG_DEF(JSMSG_NOT_A_SUBSPECIES, 73, JSEXN_NONE, 2,
		"{0} is not a member of the {1} family")

	can be used :

	JS_ReportErrorNumber(JSMSG_NOT_A_SUBSPECIES, "Rhino", "Monkey");

	to report :

	"Rhino is not a member of the Monkey family"

*/

MSG_DEF(JSMSG_NOT_AN_ERROR,             0, 0, JSEXN_NONE, "<Error #0 is reserved>")
MSG_DEF(JSMSG_NOT_DEFINED,              1, 1, JSEXN_REFERENCEERR, "{0} is not defined")
MSG_DEF(JSMSG_NO_REG_EXPS,              2, 1, JSEXN_INTERNALERR, "sorry, regular expression are not supported")
MSG_DEF(JSMSG_MORE_ARGS_NEEDED,         3, 3, JSEXN_NONE, "{0} requires more than {1} argument{2}")
MSG_DEF(JSMSG_BAD_CHAR,                 4, 1, JSEXN_NONE, "invalid format character {0}")
MSG_DEF(JSMSG_BAD_TYPE,                 5, 1, JSEXN_NONE, "unknown type {0}")
MSG_DEF(JSMSG_CANT_LOCK,                6, 0, JSEXN_NONE, "can't lock memory")
MSG_DEF(JSMSG_CANT_UNLOCK,              7, 0, JSEXN_NONE, "can't unlock memory")
MSG_DEF(JSMSG_INCOMPATIBLE_PROTO,       8, 3, JSEXN_TARGETERR, "{0}.prototype.{1} called on incompatible {2}")
MSG_DEF(JSMSG_NO_CONSTRUCTOR,           9, 1, JSEXN_NONE, "{0} has no constructor")
MSG_DEF(JSMSG_CANT_ALIAS,              10, 3, JSEXN_NONE, "can't alias {0} to {1} in class {2}")
MSG_DEF(JSMSG_NO_PROTO,                11, 1, JSEXN_INTERNALERR, "sorry, Array.prototype.{0} is not yet implemented")
MSG_DEF(JSMSG_BAD_SORT_ARG,            12, 0, JSEXN_ARRAYERR, "invalid Array.prototype.sort argument")
MSG_DEF(JSMSG_BAD_ATOMIC_NUMBER,       13, 1, JSEXN_INTERNALERR, "internal error: no index for atom {0}")
MSG_DEF(JSMSG_TOO_MANY_LITERALS,       14, 0, JSEXN_INTERNALERR, "too many literals")
MSG_DEF(JSMSG_CANT_WATCH,              15, 1, JSEXN_NONE, "can't watch non-native objects of class {0}")
MSG_DEF(JSMSG_STACK_UNDERFLOW,         16, 2, JSEXN_INTERNALERR, "internal error compiling {0}: stack underflow at pc {1}")
MSG_DEF(JSMSG_NEED_DIET,               17, 1, JSEXN_SYNTAXERR, "{0} too large")
MSG_DEF(JSMSG_BAD_CASE,                18, 2, JSEXN_SYNTAXERR, "{0}, line {1}: invalid case expression")
MSG_DEF(JSMSG_READ_ONLY,               19, 1, JSEXN_ERR, "{0} is read-only")
MSG_DEF(JSMSG_BAD_FORMAL,              20, 0, JSEXN_SYNTAXERR, "malformed formal parameter")
MSG_DEF(JSMSG_SAME_FORMAL,             21, 1, JSEXN_NONE, "duplicate formal argument {0}")
MSG_DEF(JSMSG_NOT_FUNCTION,            22, 1, JSEXN_CALLERR, "{0} is not a function")
MSG_DEF(JSMSG_NOT_CONSTRUCTOR,         23, 1, JSEXN_CONSTRUCTORERR, "{0} is not a constructor")
MSG_DEF(JSMSG_STACK_OVERFLOW,          24, 1, JSEXN_NONE, "stack overflow in {0}")
MSG_DEF(JSMSG_NOT_EXPORTED,            25, 1, JSEXN_NONE, "{0} is not exported")
MSG_DEF(JSMSG_OVER_RECURSED,           26, 0, JSEXN_NONE, "too much recursion")
MSG_DEF(JSMSG_IN_NOT_OBJECT,           27, 0, JSEXN_ERR, "target of 'in' operator must be an object")
MSG_DEF(JSMSG_BAD_NEW_RESULT,          28, 1, JSEXN_NONE, "invalid new expression result {0}")
MSG_DEF(JSMSG_BAD_SHARP_DEF,           29, 1, JSEXN_ERR, "invalid sharp variable definition #{0}=")
MSG_DEF(JSMSG_BAD_SHARP_USE,           30, 1, JSEXN_ERR, "invalid sharp variable use #{0}#")
MSG_DEF(JSMSG_BAD_INSTANCEOF_RHS,      31, 1, JSEXN_ERR, "invalid instanceof operand {0}")
MSG_DEF(JSMSG_BAD_BYTECODE,            32, 1, JSEXN_INTERNALERR, "unimplemented JavaScript bytecode {0}")
MSG_DEF(JSMSG_BAD_RADIX,               33, 1, JSEXN_ERR, "illegal radix {0}")
MSG_DEF(JSMSG_NAN,                     34, 1, JSEXN_ERR, "{0} is not a number")
MSG_DEF(JSMSG_CANT_CONVERT,            35, 1, JSEXN_TOPRIMITIVEERR, "can't convert {0} to an integer")
MSG_DEF(JSMSG_CYCLIC_VALUE,            36, 1, JSEXN_ERR, "cyclic {0} value")
MSG_DEF(JSMSG_PERMANENT,               37, 1, JSEXN_ERR, "{0} is permanent")
MSG_DEF(JSMSG_CANT_CONVERT_TO,         38, 2, JSEXN_DEFAULTVALUEERR, "can't convert {0} to {1}")
MSG_DEF(JSMSG_NO_PROPERTIES,           39, 1, JSEXN_TOOBJECTERR, "{0} has no properties")
MSG_DEF(JSMSG_CANT_FIND_CLASS,         40, 1, JSEXN_NONE, "can't find class id {0}")
MSG_DEF(JSMSG_CANT_XDR_CLASS,          41, 1, JSEXN_NONE, "can't XDR class {0}")
MSG_DEF(JSMSG_BYTECODE_TOO_BIG,        42, 2, JSEXN_INTERNALERR, "bytecode {0} too large (limit {1})")
MSG_DEF(JSMSG_UNKNOWN_FORMAT,          43, 1, JSEXN_INTERNALERR, "unknown bytecode format {0}")
MSG_DEF(JSMSG_TOO_MANY_CON_ARGS,       44, 0, JSEXN_SYNTAXERR, "too many constructor arguments")
MSG_DEF(JSMSG_TOO_MANY_FUN_ARGS,       45, 0, JSEXN_SYNTAXERR, "too many function arguments")
MSG_DEF(JSMSG_BAD_QUANTIFIER,          46, 1, JSEXN_SYNTAXERR, "invalid quantifier {0}")
MSG_DEF(JSMSG_MIN_TOO_BIG,             47, 1, JSEXN_SYNTAXERR, "overlarge minimum {0}")
MSG_DEF(JSMSG_MAX_TOO_BIG,             48, 1, JSEXN_SYNTAXERR, "overlarge maximum {0}")
MSG_DEF(JSMSG_OUT_OF_ORDER,            49, 1, JSEXN_SYNTAXERR, "maximum {0} less than minimum")
MSG_DEF(JSMSG_ZERO_QUANTIFIER,         50, 1, JSEXN_SYNTAXERR, "zero quantifier {0}")
MSG_DEF(JSMSG_UNTERM_QUANTIFIER,       51, 1, JSEXN_SYNTAXERR, "unterminated quantifier {0}")
MSG_DEF(JSMSG_EMPTY_BEFORE_STAR,       52, 0, JSEXN_SYNTAXERR, "regular expression before * could be empty")
MSG_DEF(JSMSG_EMPTY_BEFORE_PLUS,       53, 0, JSEXN_SYNTAXERR, "regular expression before + could be empty")
MSG_DEF(JSMSG_MISSING_PAREN,           54, 1, JSEXN_SYNTAXERR, "unterminated parenthetical {0}")
MSG_DEF(JSMSG_UNTERM_CLASS,            55, 1, JSEXN_SYNTAXERR, "unterminated character class {0}")
MSG_DEF(JSMSG_TRAILING_SLASH,          56, 0, JSEXN_SYNTAXERR, "trailing \\ in regular expression")
MSG_DEF(JSMSG_BAD_CLASS_RANGE,         57, 0, JSEXN_SYNTAXERR, "invalid range in character class")
MSG_DEF(JSMSG_BAD_FLAG,                58, 1, JSEXN_SYNTAXERR, "invalid regular expression flag {0}")
MSG_DEF(JSMSG_NO_INPUT,                59, 3, JSEXN_SYNTAXERR, "no input for /{0}/{1}{2}")
MSG_DEF(JSMSG_CANT_OPEN,               60, 2, JSEXN_NONE, "can't open {0}: {1}")
MSG_DEF(JSMSG_BAD_STRING_MASK,         61, 1, JSEXN_ERR, "invalid string escape mask {0}")
MSG_DEF(JSMSG_NO_STRING_PROTO,         62, 1, JSEXN_INTERNALERR, "sorry, String.prototype.{0} is not yet implemented")
MSG_DEF(JSMSG_END_OF_DATA,             63, 0, JSEXN_NONE, "unexpected end of data")
MSG_DEF(JSMSG_SEEK_BEYOND_START,       64, 0, JSEXN_NONE, "illegal seek beyond start")
MSG_DEF(JSMSG_SEEK_BEYOND_END,         65, 0, JSEXN_NONE, "illegal seek beyond end")
MSG_DEF(JSMSG_END_SEEK,                66, 0, JSEXN_NONE, "illegal end-based seek")
MSG_DEF(JSMSG_WHITHER_WHENCE,          67, 1, JSEXN_NONE, "unknown seek whence: {0}")
MSG_DEF(JSMSG_BAD_JVAL_TYPE,           68, 1, JSEXN_NONE, "unknown jsval type {0} for XDR")
MSG_DEF(JSMSG_PAREN_BEFORE_FORMAL,     69, 0, JSEXN_SYNTAXERR, "missing ( before formal parameters")
MSG_DEF(JSMSG_MISSING_FORMAL,          70, 0, JSEXN_SYNTAXERR, "missing formal parameter")
MSG_DEF(JSMSG_PAREN_AFTER_FORMAL,      71, 0, JSEXN_SYNTAXERR, "missing ) after formal parameters")
MSG_DEF(JSMSG_CURLY_BEFORE_BODY,       72, 0, JSEXN_SYNTAXERR, "missing { before function body")
MSG_DEF(JSMSG_CURLY_AFTER_BODY,        73, 0, JSEXN_SYNTAXERR, "missing } after function body")
MSG_DEF(JSMSG_PAREN_BEFORE_COND,       74, 0, JSEXN_SYNTAXERR, "missing ( before condition")
MSG_DEF(JSMSG_PAREN_AFTER_COND,        75, 0, JSEXN_SYNTAXERR, "missing ) after condition")
MSG_DEF(JSMSG_NO_IMPORT_NAME,          76, 0, JSEXN_SYNTAXERR, "missing name in import statement")
MSG_DEF(JSMSG_NAME_AFTER_DOT,          77, 0, JSEXN_SYNTAXERR, "missing name after . operator")
MSG_DEF(JSMSG_BRACKET_IN_INDEX,        78, 0, JSEXN_SYNTAXERR, "missing ] in index expression")
MSG_DEF(JSMSG_NO_EXPORT_NAME,          79, 0, JSEXN_SYNTAXERR, "missing name in export statement")
MSG_DEF(JSMSG_PAREN_BEFORE_SWITCH,     80, 0, JSEXN_SYNTAXERR, "missing ( before switch expression")
MSG_DEF(JSMSG_PAREN_AFTER_SWITCH,      81, 0, JSEXN_SYNTAXERR, "missing ) after switch expression")
MSG_DEF(JSMSG_CURLY_BEFORE_SWITCH,     82, 0, JSEXN_SYNTAXERR, "missing { before switch body")
MSG_DEF(JSMSG_COLON_AFTER_CASE,        83, 0, JSEXN_SYNTAXERR, "missing : after case label")
MSG_DEF(JSMSG_WHILE_AFTER_DO,          84, 0, JSEXN_SYNTAXERR, "missing while after do-loop body")
MSG_DEF(JSMSG_PAREN_AFTER_FOR,         85, 0, JSEXN_SYNTAXERR, "missing ( after for")
MSG_DEF(JSMSG_SEMI_AFTER_FOR_INIT,     86, 0, JSEXN_SYNTAXERR, "missing ; after for-loop initializer")
MSG_DEF(JSMSG_SEMI_AFTER_FOR_COND,     87, 0, JSEXN_SYNTAXERR, "missing ; after for-loop condition")
MSG_DEF(JSMSG_PAREN_AFTER_FOR_CTRL,    88, 0, JSEXN_SYNTAXERR, "missing ) after for-loop control")
MSG_DEF(JSMSG_CURLY_BEFORE_TRY,        89, 0, JSEXN_SYNTAXERR, "missing { before try block")
MSG_DEF(JSMSG_CURLY_AFTER_TRY,         90, 0, JSEXN_SYNTAXERR, "missing } after try block")
MSG_DEF(JSMSG_PAREN_BEFORE_CATCH,      91, 0, JSEXN_SYNTAXERR, "missing ( before catch")
MSG_DEF(JSMSG_CATCH_IDENTIFIER,        92, 0, JSEXN_SYNTAXERR, "missing identifier in catch")
MSG_DEF(JSMSG_PAREN_AFTER_CATCH,       93, 0, JSEXN_SYNTAXERR, "missing ) after catch")
MSG_DEF(JSMSG_CURLY_BEFORE_CATCH,      94, 0, JSEXN_SYNTAXERR, "missing { before catch block")
MSG_DEF(JSMSG_CURLY_AFTER_CATCH,       95, 0, JSEXN_SYNTAXERR, "missing } after catch block")
MSG_DEF(JSMSG_CURLY_BEFORE_FINALLY,    96, 0, JSEXN_SYNTAXERR, "missing { before finally block")
MSG_DEF(JSMSG_CURLY_AFTER_FINALLY,     97, 0, JSEXN_SYNTAXERR, "missing } after finally block")
MSG_DEF(JSMSG_CATCH_OR_FINALLY,        98, 0, JSEXN_SYNTAXERR, "missing catch or finally after try")
MSG_DEF(JSMSG_PAREN_BEFORE_WITH,       99, 0, JSEXN_SYNTAXERR, "missing ( before with-statement object")
MSG_DEF(JSMSG_PAREN_AFTER_WITH,       100, 0, JSEXN_SYNTAXERR, "missing ) after with-statement object")
MSG_DEF(JSMSG_CURLY_IN_COMPOUND,      101, 0, JSEXN_SYNTAXERR, "missing } in compound statement")
MSG_DEF(JSMSG_NO_VARIABLE_NAME,       102, 0, JSEXN_SYNTAXERR, "missing variable name")
MSG_DEF(JSMSG_COLON_IN_COND,          103, 0, JSEXN_SYNTAXERR, "missing : in conditional expression")
MSG_DEF(JSMSG_PAREN_AFTER_ARGS,       104, 0, JSEXN_SYNTAXERR, "missing ) after argument list")
MSG_DEF(JSMSG_BRACKET_AFTER_LIST,     105, 0, JSEXN_SYNTAXERR, "missing ] after element list")
MSG_DEF(JSMSG_COLON_AFTER_ID,         106, 0, JSEXN_SYNTAXERR, "missing : after property id")
MSG_DEF(JSMSG_CURLY_AFTER_LIST,       107, 0, JSEXN_SYNTAXERR, "missing } after property list")
MSG_DEF(JSMSG_PAREN_IN_PAREN,         108, 0, JSEXN_SYNTAXERR, "missing ) in parenthetical")
MSG_DEF(JSMSG_SEMI_BEFORE_STMNT,      109, 0, JSEXN_SYNTAXERR, "missing ; before statement")
MSG_DEF(JSMSG_NO_RETURN_VALUE,        110, 0, JSEXN_NONE, "function does not always return a value")
MSG_DEF(JSMSG_DUPLICATE_FORMAL,       111, 1, JSEXN_NONE, "duplicate formal argument {0}")
MSG_DEF(JSMSG_EQUAL_AS_ASSIGN,        112, 1, JSEXN_NONE, "test for equality (==) mistyped as assignment (=)?{0}")
MSG_DEF(JSMSG_BAD_IMPORT,             113, 0, JSEXN_SYNTAXERR, "invalid import expression")
MSG_DEF(JSMSG_TOO_MANY_DEFAULTS,      114, 0, JSEXN_SYNTAXERR, "more than one switch default")
MSG_DEF(JSMSG_TOO_MANY_CASES,         115, 0, JSEXN_INTERNALERR, "too many switch cases")
MSG_DEF(JSMSG_BAD_SWITCH,             116, 0, JSEXN_SYNTAXERR, "invalid switch statement")
MSG_DEF(JSMSG_BAD_FOR_LEFTSIDE,       117, 0, JSEXN_SYNTAXERR, "invalid for/in left-hand side")
MSG_DEF(JSMSG_CATCH_AFTER_GENERAL,    118, 0, JSEXN_NONE, "catch clause after general catch")
MSG_DEF(JSMSG_CATCH_WITHOUT_TRY,      119, 0, JSEXN_SYNTAXERR, "catch without try")
MSG_DEF(JSMSG_FINALLY_WITHOUT_TRY,    120, 0, JSEXN_SYNTAXERR, "finally without try")
MSG_DEF(JSMSG_LABEL_NOT_FOUND,        121, 0, JSEXN_SYNTAXERR, "label not found")
MSG_DEF(JSMSG_TOUGH_BREAK,            122, 0, JSEXN_SYNTAXERR, "invalid break")
MSG_DEF(JSMSG_BAD_CONTINUE,           123, 0, JSEXN_SYNTAXERR, "invalid continue")
MSG_DEF(JSMSG_BAD_RETURN,             124, 0, JSEXN_SYNTAXERR, "invalid return")
MSG_DEF(JSMSG_BAD_LABEL,              125, 0, JSEXN_SYNTAXERR, "invalid label")
MSG_DEF(JSMSG_DUPLICATE_LABEL,        126, 0, JSEXN_SYNTAXERR, "duplicate label")
MSG_DEF(JSMSG_VAR_HIDES_ARG,          127, 1, JSEXN_NONE, "variable {0} hides argument")
MSG_DEF(JSMSG_BAD_VAR_INIT,           128, 0, JSEXN_SYNTAXERR, "invalid variable initialization")
MSG_DEF(JSMSG_BAD_LEFTSIDE_OF_ASS,    129, 0, JSEXN_SYNTAXERR, "invalid assignment left-hand side")
MSG_DEF(JSMSG_BAD_OPERAND,            130, 1, JSEXN_SYNTAXERR, "invalid {0} operand")
MSG_DEF(JSMSG_BAD_PROP_ID,            131, 0, JSEXN_SYNTAXERR, "invalid property id")
MSG_DEF(JSMSG_RESERVED_ID,            132, 1, JSEXN_SYNTAXERR, "{0} is a reserved identifier")
MSG_DEF(JSMSG_SYNTAX_ERROR,           133, 0, JSEXN_SYNTAXERR, "syntax error")
MSG_DEF(JSMSG_BAD_SHARP_VAR_DEF,      134, 0, JSEXN_SYNTAXERR, "invalid sharp variable definition")
MSG_DEF(JSMSG_BAD_PROTOTYPE,          135, 1, JSEXN_ERR, "'prototype' property of {0} is not an object")
MSG_DEF(JSMSG_MISSING_EXPONENT,       136, 0, JSEXN_SYNTAXERR, "missing exponent")
MSG_DEF(JSMSG_OUT_OF_MEMORY,          137, 0, JSEXN_ERR, "out of memory")
MSG_DEF(JSMSG_UNTERMINATED_STRING,    138, 0, JSEXN_SYNTAXERR, "unterminated string literal")
MSG_DEF(JSMSG_NESTED_COMMENT,         139, 0, JSEXN_SYNTAXERR, "nested comment")
MSG_DEF(JSMSG_UNTERMINATED_COMMENT,   140, 0, JSEXN_SYNTAXERR, "unterminated comment")
MSG_DEF(JSMSG_UNTERMINATED_REGEXP,    141, 0, JSEXN_SYNTAXERR, "unterminated regular expression literal")
MSG_DEF(JSMSG_BAD_REGEXP_FLAG,        142, 0, JSEXN_SYNTAXERR, "invalid flag after regular expression")
MSG_DEF(JSMSG_SHARPVAR_TOO_BIG,       143, 0, JSEXN_SYNTAXERR, "overlarge sharp variable number")
MSG_DEF(JSMSG_ILLEGAL_CHARACTER,      144, 0, JSEXN_SYNTAXERR, "illegal character")
MSG_DEF(JSMSG_BAD_OCTAL,              145, 1, JSEXN_NONE, "{0} is not a legal ECMA-262 numeric constant")
MSG_DEF(JSMSG_BAD_INDIRECT_CALL,      146, 1, JSEXN_CALLERR, "function {0} must be called directly, and not by way of a function of another name.")
MSG_DEF(JSMSG_UNCAUGHT_EXCEPTION,     147, 1, JSEXN_NONE, "uncaught exception: {0}")
