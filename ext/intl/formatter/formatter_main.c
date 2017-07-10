/*
   +----------------------------------------------------------------------+
   | PHP Version 7                                                        |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Stanislav Malyshev <stas@zend.com>                          |
   +----------------------------------------------------------------------+
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <unicode/ustring.h>

#include "php_intl.h"
#include "formatter_class.h"
#include "intl_convert.h"

/* {{{ */
static int numfmt_ctor(INTERNAL_FUNCTION_PARAMETERS, zend_bool is_constructor)
{
	const char* locale;
	char*       pattern = NULL;
	size_t      locale_len = 0, pattern_len = 0;
	zend_long   style;
	UChar*      spattern     = NULL;
	int32_t     spattern_len = 0;
	int         zpp_flags = is_constructor ? ZEND_PARSE_PARAMS_THROW : 0;
	FORMATTER_METHOD_INIT_VARS;

	/* Parse parameters. */
	if( zend_parse_parameters_ex( zpp_flags, ZEND_NUM_ARGS(), "sl|s",
		&locale, &locale_len, &style, &pattern, &pattern_len ) == FAILURE )
	{
		intl_error_set( NULL, U_ILLEGAL_ARGUMENT_ERROR,
			"numfmt_create: unable to parse input parameters", 0 );
		return FAILURE;
	}

	INTL_CHECK_LOCALE_LEN_OR_FAILURE(locale_len);
	object = return_value;
	FORMATTER_METHOD_FETCH_OBJECT_NO_CHECK;

	/* Convert pattern (if specified) to UTF-16. */
	if(pattern && pattern_len) {
		intl_convert_utf8_to_utf16(&spattern, &spattern_len, pattern, pattern_len, &INTL_DATA_ERROR_CODE(nfo));
		INTL_CTOR_CHECK_STATUS(nfo, "numfmt_create: error converting pattern to UTF-16");
	}

	if(locale_len == 0) {
		locale = intl_locale_get_default();
	}

	/* Create an ICU number formatter. */
	FORMATTER_OBJECT(nfo) = unum_open(style, spattern, spattern_len, locale, NULL, &INTL_DATA_ERROR_CODE(nfo));

	zend_update_property_string(NumberFormatter_ce_ptr, object, "locale", sizeof("locale") - 1, locale);
	zend_update_property_long(NumberFormatter_ce_ptr, object, "style", sizeof("style") - 1, style);
	if (pattern) {
		zend_update_property_string(NumberFormatter_ce_ptr, object, "pattern", sizeof("pattern") - 1, pattern);
	}

	if(spattern) {
		efree(spattern);
	}

	INTL_CTOR_CHECK_STATUS(nfo, "numfmt_create: number formatter creation failed");
	return SUCCESS;
}
/* }}} */

/* {{{ proto NumberFormatter NumberFormatter::create( string $locale, int style[, string $pattern ] )
 * Create number formatter. }}} */
/* {{{ proto NumberFormatter numfmt_create( string $locale, int style[, string $pattern ] )
 * Create number formatter.
 */
PHP_FUNCTION( numfmt_create )
{
	object_init_ex( return_value, NumberFormatter_ce_ptr );
	if (numfmt_ctor(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0) == FAILURE) {
		zval_ptr_dtor(return_value);
		RETURN_NULL();
	}
}
/* }}} */

/* {{{ proto void NumberFormatter::__construct( string $locale, int style[, string $pattern ] )
 * NumberFormatter object constructor.
 */
PHP_METHOD( NumberFormatter, __construct )
{
	zend_error_handling error_handling;

	zend_replace_error_handling(EH_THROW, IntlException_ce_ptr, &error_handling);
	return_value = getThis();
	if (numfmt_ctor(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1) == FAILURE) {
		if (!EG(exception)) {
			zend_throw_exception(IntlException_ce_ptr, "Constructor failed", 0);
		}
	}
	zend_restore_error_handling(&error_handling);
}
/* }}} */

/* {{{ proto void NumberFormatter::__wakeup()
 * NumberFormatter object unserializer.
 */
PHP_METHOD( NumberFormatter, __wakeup )
{
		const char* locale = NULL;
		size_t      pattern_len = 0;
		char*       pattern = NULL;
		zend_long   style = 0;
		UChar*      spattern     = NULL;
		int32_t     spattern_len = 0;
		zval        rv;
		zval        *z_locale, *z_style, *z_pattern;
		zend_string *zstr_locale, *zstr_pattern = NULL;

		return_value = getThis();

		z_locale = zend_read_property(Z_OBJCE_P(return_value), return_value, "locale", sizeof("locale") - 1, 0, &rv);
		if (z_locale == NULL || Z_TYPE_P(z_locale) != IS_STRING) {
			return;
		}

		zstr_locale = zval_get_string(z_locale);
		locale = ZSTR_VAL(zstr_locale);


		z_style = zend_read_property(Z_OBJCE_P(return_value), return_value, "style", sizeof("style") - 1, 0, &rv);
		if (z_style != NULL && Z_TYPE_P(z_style) == IS_LONG) {
			style = zval_get_long(z_style);
		}

		z_pattern = zend_read_property(Z_OBJCE_P(return_value), return_value, "pattern", sizeof("pattern") - 1, 0, &rv);
		if (z_pattern != NULL && Z_TYPE_P(z_pattern) == IS_STRING) {
			zstr_pattern = zval_get_string(z_pattern);
			pattern = ZSTR_VAL(zstr_pattern);
			pattern_len = ZSTR_LEN(zstr_pattern);
		}

		FORMATTER_METHOD_INIT_VARS;

		object = return_value;
		nfo = Z_INTL_NUMBERFORMATTER_P(object);

		/* Convert pattern (if specified) to UTF-16. */
		if(pattern && pattern_len) {
			intl_convert_utf8_to_utf16(&spattern, &spattern_len, pattern, pattern_len, &INTL_DATA_ERROR_CODE(nfo));
			if (INTL_DATA_ERROR_CODE(nfo) != U_ZERO_ERROR) {
					intl_errors_set(&nfo->nf_data.error, INTL_DATA_ERROR_CODE(nfo),
						"Unserializing NumberFormatter failed", 0);
					if(spattern) {
						efree(spattern);
					}
					zend_string_release(zstr_locale);
					if (zstr_pattern != NULL) {
						zend_string_release(zstr_pattern);
					}
					return;
			}
		}

		/* Create an ICU number formatter. */
		FORMATTER_OBJECT(nfo) = unum_open(style, spattern, spattern_len, locale, NULL, &INTL_DATA_ERROR_CODE(nfo));

		if(spattern) {
			efree(spattern);
		}

		zend_string_release(zstr_locale);
		if (zstr_pattern != NULL) {
			zend_string_release(zstr_pattern);
		}
		intl_errors_set(&nfo->nf_data.error, INTL_DATA_ERROR_CODE(nfo),
			"Unserializing NumberFormatter instance failed", 0);
}
/* }}} */

/* {{{ proto int NumberFormatter::getErrorCode()
 * Get formatter's last error code. }}} */
/* {{{ proto int numfmt_get_error_code( NumberFormatter $nf )
 * Get formatter's last error code.
 */
PHP_FUNCTION( numfmt_get_error_code )
{
	FORMATTER_METHOD_INIT_VARS

	/* Parse parameters. */
	if( zend_parse_method_parameters( ZEND_NUM_ARGS(), getThis(), "O",
		&object, NumberFormatter_ce_ptr ) == FAILURE )
	{
		intl_error_set( NULL, U_ILLEGAL_ARGUMENT_ERROR,
			"numfmt_get_error_code: unable to parse input params", 0 );

		RETURN_FALSE;
	}

	nfo = Z_INTL_NUMBERFORMATTER_P(object);

	/* Return formatter's last error code. */
	RETURN_LONG( INTL_DATA_ERROR_CODE(nfo) );
}
/* }}} */

/* {{{ proto string NumberFormatter::getErrorMessage( )
 * Get text description for formatter's last error code. }}} */
/* {{{ proto string numfmt_get_error_message( NumberFormatter $nf )
 * Get text description for formatter's last error code.
 */
PHP_FUNCTION( numfmt_get_error_message )
{
	zend_string *message = NULL;
	FORMATTER_METHOD_INIT_VARS

	/* Parse parameters. */
	if( zend_parse_method_parameters( ZEND_NUM_ARGS(), getThis(), "O",
		&object, NumberFormatter_ce_ptr ) == FAILURE )
	{
		intl_error_set( NULL, U_ILLEGAL_ARGUMENT_ERROR,
			"numfmt_get_error_message: unable to parse input params", 0 );

		RETURN_FALSE;
	}

	nfo = Z_INTL_NUMBERFORMATTER_P(object);

	/* Return last error message. */
	message = intl_error_get_message( INTL_DATA_ERROR_P(nfo) );
	RETURN_STR(message);
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
