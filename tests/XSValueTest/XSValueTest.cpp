/*
 * Copyright 1999-2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
* $Id$
* $Log$
* Revision 1.12  2004/11/14 19:02:21  peiyongz
* error status for numeric data types tested
*
* Revision 1.11  2004/09/13 21:25:11  peiyongz
* DATATYPE_TEST added
*
* Revision 1.10  2004/09/10 13:55:00  peiyongz
* to run on 64 box
*
* Revision 1.9  2004/09/09 20:10:04  peiyongz
* Using new error code
*
* Revision 1.8  2004/09/08 19:56:32  peiyongz
* Remove parameter toValidate from validation interface
*
* Revision 1.7  2004/09/08 13:57:06  peiyongz
* Apache License Version 2.0
*
* Revision 1.6  2004/08/31 20:53:43  peiyongz
* Testing time zone
*
* Revision 1.5  2004/08/31 15:15:16  peiyongz
* remove XSValueContext
*
* Revision 1.4  2004/08/24 16:00:15  peiyongz
* To build on AIX/Win2003-ecl
*
* Revision 1.3  2004/08/23 17:07:57  peiyongz
* Minimum representable range on all platforms
*
* Revision 1.2  2004/08/19 21:29:28  peiyongz
* no message
*
* Revision 1.1  2004/08/19 17:17:21  peiyongz
* XSValueTest
*
*
*/

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "XSValueTest.hpp"

#include <xercesc/validators/schema/SchemaSymbols.hpp>
#include <xercesc/util/XMLUni.hpp>

#if defined(XERCES_NEW_IOSTREAMS)
#include <fstream>
#else
#include <fstream.h>
#endif

#include <stdio.h>

#include <xercesc/framework/psvi/XSValue.hpp>
#include <xercesc/util/PlatformUtils.hpp>

static const bool  EXP_RET_VALID_TRUE  = true;
static const bool  EXP_RET_VALUE_TRUE  = true;
static const bool  EXP_RET_CANREP_TRUE = true;

static const bool  EXP_RET_VALID_FALSE  = false;
static const bool  EXP_RET_VALUE_FALSE  = false;
static const bool  EXP_RET_CANREP_FALSE = false;

static const XSValue::Status DONT_CARE = XSValue::st_UnknownType;
static bool  errSeen = false;

const XMLCh* getDataTypeString(const XSValue::DataType dt)
{
    switch(dt)
    {
    case XSValue::dt_string:
        return SchemaSymbols::fgDT_STRING;
    case XSValue::dt_boolean:
        return SchemaSymbols::fgDT_BOOLEAN;
    case XSValue::dt_decimal:
        return SchemaSymbols::fgDT_DECIMAL;
    case XSValue::dt_float:
        return SchemaSymbols::fgDT_FLOAT;
    case XSValue::dt_double:
        return SchemaSymbols::fgDT_DOUBLE;      
    case XSValue::dt_duration:
        return SchemaSymbols::fgDT_DURATION;  
    case XSValue::dt_dateTime:
        return SchemaSymbols::fgDT_DATETIME;   
    case XSValue::dt_time:
        return SchemaSymbols::fgDT_TIME;      
    case XSValue::dt_date:
        return SchemaSymbols::fgDT_DATE; 
    case XSValue::dt_gYearMonth:
        return SchemaSymbols::fgDT_YEARMONTH; 
    case XSValue::dt_gYear:
        return SchemaSymbols::fgDT_YEAR; 
    case XSValue::dt_gMonthDay:
        return SchemaSymbols::fgDT_MONTHDAY;  
    case XSValue::dt_gDay:
        return SchemaSymbols::fgDT_DAY;   
    case XSValue::dt_gMonth:
        return SchemaSymbols::fgDT_MONTH;  
    case XSValue::dt_hexBinary:
        return SchemaSymbols::fgDT_HEXBINARY; 
    case XSValue::dt_base64Binary:
        return SchemaSymbols::fgDT_BASE64BINARY; 
    case XSValue::dt_anyURI:
        return SchemaSymbols::fgDT_ANYURI;   
    case XSValue::dt_QName:
        return SchemaSymbols::fgDT_QNAME; 
    case XSValue::dt_NOTATION:
        XMLUni::fgNotationString;   
    case XSValue::dt_normalizedString:
        return SchemaSymbols::fgDT_NORMALIZEDSTRING; 
    case XSValue::dt_token:
        return SchemaSymbols::fgDT_TOKEN;         
    case XSValue::dt_language:
        return SchemaSymbols::fgDT_LANGUAGE;    
    case XSValue::dt_NMTOKEN:
        return XMLUni::fgNmTokenString;       
    case XSValue::dt_NMTOKENS:
        return XMLUni::fgNmTokensString;   
    case XSValue::dt_Name:
        return SchemaSymbols::fgDT_NAME;     
    case XSValue::dt_NCName:
        return SchemaSymbols::fgDT_NCNAME;  
    case XSValue::dt_ID:
        return XMLUni::fgIDString; 
    case XSValue::dt_IDREF:
        return XMLUni::fgIDRefString;   
    case XSValue::dt_IDREFS:
        return XMLUni::fgIDRefsString; 
    case XSValue::dt_ENTITY:
        return XMLUni::fgEntityString; 
    case XSValue::dt_ENTITIES:
        return XMLUni::fgEntitiesString;  
    case XSValue::dt_integer:
        return SchemaSymbols::fgDT_INTEGER;  
    case XSValue::dt_nonPositiveInteger:
        return SchemaSymbols::fgDT_NONPOSITIVEINTEGER; 
    case XSValue::dt_negativeInteger:
        return SchemaSymbols::fgDT_NEGATIVEINTEGER;
    case XSValue::dt_long:
        return SchemaSymbols::fgDT_LONG; 
    case XSValue::dt_int:
        return SchemaSymbols::fgDT_INT;  
    case XSValue::dt_short:
        return SchemaSymbols::fgDT_SHORT; 
    case XSValue::dt_byte:
        return SchemaSymbols::fgDT_BYTE;  
    case XSValue::dt_nonNegativeInteger:
        return SchemaSymbols::fgDT_NONNEGATIVEINTEGER;
    case XSValue::dt_unsignedLong:
        return SchemaSymbols::fgDT_ULONG; 
    case XSValue::dt_unsignedInt:
        return SchemaSymbols::fgDT_UINT;
    case XSValue::dt_unsignedShort:
        return SchemaSymbols::fgDT_USHORT;  
    case XSValue::dt_unsignedByte:
        return SchemaSymbols::fgDT_UBYTE;     
    case XSValue::dt_positiveInteger:
        return SchemaSymbols::fgDT_POSITIVEINTEGER;
    default:
        return 0;
    }
}

char* getStatusString(const XSValue::Status status)
{
    switch (status)
    { 
    case XSValue::st_Init:
        return "st_Init";
        break;
    case XSValue::st_NoContent:
        return "st_NoContent";
        break;
    case XSValue::st_NoCanRep:
        return "st_NoCanRep";
        break;
    case XSValue::st_NoActVal:
        return "st_NoActVal";
        break;
    case XSValue::st_NotSupported:
        return "st_NotSupported";
        break;
    case XSValue::st_CantCreateRegEx:
        return "st_CantCreateRegEx";
        break;
    case XSValue::st_FOCA0002:
        return "st_FOCA0002";
        break;
    case XSValue::st_FOCA0001:
        return "st_FOCA0001";
        break;
    case XSValue::st_FOCA0003:
        return "st_FOCA0003";
        break;
    case XSValue::st_FODT0003:
        return "st_FODT0003";
        break;
    case XSValue::st_UnknownType:
        return "st_UnknownType";
        break;
    default:
        return "st_UnknownType";
        break;
    }
   
}

/**
 * This is to test methods for XSValue
 */


#ifdef _DEBUG
void VALIDATE_TEST( const char*                  const  data
                  , const XSValue::DataType             datatype
                  ,       bool                          expRetValid
                  , const XSValue::Status               expStatus
                  )
{
    XSValue::Status myStatus = XSValue::st_Init;

    bool actRetValid = XSValue::validate(
                                          StrX(data).unicodeForm()
                                        , datatype
                                        , myStatus
                                        , XSValue::ver_10
                                        , XMLPlatformUtils::fgMemoryManager);

    if (actRetValid != expRetValid)
    {
        printf("VALIDATE_TEST Validation Fail: data=<%s>, datatype=<%s>, expRetVal=<%d>\n",
                data, StrX(getDataTypeString(datatype)).localForm(), expRetValid);
        errSeen = true;
    }
    else 
    {
        if (!expRetValid             && 
             expStatus != DONT_CARE  && 
             expStatus != myStatus ) 
        {
            printf("VALIDATE_TEST Context Diff, data=<%s> datatype=<%s>, expStatus=<%s>, actStatus=<%s>\n",
                    data, StrX(getDataTypeString(datatype)).localForm(), getStatusString(expStatus), getStatusString(myStatus));
            errSeen = true;
        }
    }
}
#else
#define VALIDATE_TEST(data, datatype, expRetValid, expStatus)                        \
{                                                                                    \
    XSValue::Status myStatus = XSValue::st_Init;                                     \
    bool actRetValid = XSValue::validate(                                            \
                                          StrX(data).unicodeForm()                   \
                                        , datatype                                   \
                                        , myStatus                                   \
                                        , XSValue::ver_10                            \
                                        , XMLPlatformUtils::fgMemoryManager);        \
    if (actRetValid != expRetValid) {                                                \
        printf("VALIDATE_TEST Validation Fail:                                       \
                at line <%d>, data=<%s>, datatype=<%s>, expRetVal=<%d>\n"            \
              , __LINE__, data, StrX(getDataTypeString(datatype)).localForm()        \
              , expRetValid);                                                        \
        errSeen = true;                                                              \
    }                                                                                \
    else {                                                                           \
        if (!expRetValid             &&                                              \
             expStatus != DONT_CARE  &&                                              \
             expStatus != myStatus ) {                                               \
             printf("VALIDATE_TEST Context Diff,                                     \
                   at line <%d>, data=<%s> datatype=<%s>,                            \
                   expStatus=<%s>, actStatus=<%s>\n"                                 \
                  , __LINE__, data, StrX(getDataTypeString(datatype)).localForm(),   \
                  getStatusString(expStatus), getStatusString(myStatus));            \
             errSeen = true;                                                         \
        }                                                                            \
    }                                                                                \
}
#endif

#ifdef _DEBUG
void ACTVALUE_TEST(  const char*                  const  data
                   , const XSValue::DataType             datatype
                   ,       bool                          toValidate
                   ,       bool                          expRetValue
                   , const XSValue::Status               expStatus
                    )
{
    XSValue::Status myStatus = XSValue::st_Init;

    XSValue* actRetValue = XSValue::getActualValue(
                                                   StrX(data).unicodeForm()
                                                 , datatype
                                                 , myStatus
                                                 , XSValue::ver_10
                                                 , toValidate
                                                 , XMLPlatformUtils::fgMemoryManager);
    if (actRetValue) 
    {
        if (!expRetValue) 
        {
            printf("ACTVALUE_TEST XSValue returned: data=<%s>, datatype=<%s>\n",
                    data, StrX(getDataTypeString(datatype)).localForm());
            errSeen = true;
        }                                                                            

        delete actRetValue;
    }
    else 
    {
        if (expRetValue) 
        {
            printf("ACTVALUE_TEST No XSValue returned, data=<%s>, datatype=<%s>\n" ,
                    data, StrX(getDataTypeString(datatype)).localForm());
            errSeen = true;
        }
        else
        {
            if (expStatus != DONT_CARE  &&
                expStatus != myStatus    ) 
            {
                printf("ACTVALUE_TEST Context Diff, data=<%s>, datatype=<%s>, expStatus=<%s>, actStatus=<%s>\n" ,
                       data, StrX(getDataTypeString(datatype)).localForm(), getStatusString(expStatus), getStatusString(myStatus));
                errSeen = true;
            }
        }
    }
}
#else
#define ACTVALUE_TEST(data, datatype, toValidate, expRetValue, expStatus)              \
{                                                                                      \
    XSValue::Status myStatus = XSValue::st_Init;                                       \
    XSValue* actRetValue = XSValue::getActualValue(                                    \
                                                   StrX(data).unicodeForm()            \
                                                 , datatype                            \
                                                 , myStatus                            \
                                                 , XSValue::ver_10                     \
                                                 , toValidate                          \
                                                 , XMLPlatformUtils::fgMemoryManager); \
    if (actRetValue) {                                                                 \
       if (!expRetValue) {                                                             \
            printf("ACTVALUE_TEST XSValue returned,                                    \
                    at line <%d> data=<%s>, datatype=<%s>\n"                           \
                  ,__LINE__, data, StrX(getDataTypeString(datatype)).localForm());     \
            errSeen = true;                                                            \
       }                                                                               \
       delete actRetValue;                                                             \
    }                                                                                  \
    else {                                                                             \
        if (expRetValue) {                                                             \
            printf("ACTVALUE_TEST No XSValue returned,                                 \
                    at line <%d> data=<%s>, datatype=<%s>\n"                           \
                  , __LINE__, data, StrX(getDataTypeString(datatype)).localForm());    \
            errSeen = true;                                                            \
         }                                                                             \
         else {                                                                        \
             if (expStatus != DONT_CARE &&                                             \
                 expStatus != myStatus) {                                              \
                 printf("ACTVALUE_TEST Context Diff,                                   \
                         at line <%d> data=<%s>, datatype=<%s>,                        \
                         expStatus=<%s>, actStatus=<%s>\n"                             \
                        , __LINE__, data, StrX(getDataTypeString(datatype)).localForm() \
                        , getStatusString(expStatus), getStatusString(myStatus));      \
                 errSeen = true;                                                       \
             }                                                                         \
        }                                                                              \
    }                                                                                  \
}
#endif

#ifdef _DEBUG
void CANREP_TEST(const char*                  const  data
               , const XSValue::DataType             datatype
               ,       bool                          toValidate
               ,       bool                          expRetCanRep
               , const char*                  const  toCompare
               , const XSValue::Status               expStatus
                )
{
    XSValue::Status myStatus = XSValue::st_Init;

    XMLCh* actRetCanRep = XSValue::getCanonicalRepresentation(
                                                            StrX(data).unicodeForm()
                                                          , datatype
                                                          , myStatus
                                                          , XSValue::ver_10
                                                          , toValidate
                                                          , XMLPlatformUtils::fgMemoryManager);
    if (actRetCanRep)
    {
        if (!expRetCanRep)
        {
            printf("CANREP_TEST CanRep returned, data=<%s>, datatype=<%s>\n" ,
                    data, StrX(getDataTypeString(datatype)).localForm());
            XMLPlatformUtils::fgMemoryManager->deallocate(actRetCanRep);
            errSeen = true;
        }
        else
        {
            char* actRetCanRep_inchar = XMLString::transcode(actRetCanRep);

            if (!XMLString::equals(actRetCanRep_inchar, toCompare)) 
            {
                printf("CANREP_TEST CanRep Diff , data=<%s>, datatype=<%s>, actCanRep=<%s>, toCompare=<%s>\n" ,
                    data, StrX(getDataTypeString(datatype)).localForm(), actRetCanRep_inchar, toCompare);
                errSeen = true;
            }

            XMLPlatformUtils::fgMemoryManager->deallocate(actRetCanRep);
            XMLString::release(&actRetCanRep_inchar);
        }
    }                                                                                 
    else 
    {                                                                            
        if (expRetCanRep)
        {
            printf("CANREP_TEST No CanRep returned, data=<%s>, datatype=<%s>\n" ,
                    data, StrX(getDataTypeString(datatype)).localForm());
            errSeen = true;
        }
        else
        {
            if (expStatus != DONT_CARE  &&
                expStatus != myStatus    )
            {
                printf("CANREP_TEST Context Diff, data=<%s>, datatype=<%s>\n expStatus=<%s>, actStatus=<%s>\n" ,
                    data, StrX(getDataTypeString(datatype)).localForm(), getStatusString(expStatus), getStatusString(myStatus));
                errSeen = true;
            }
        }
    }                                                                                 
}
#else
#define CANREP_TEST(data, datatype, toValidate, expRetCanRep, toCompare, expStatus)   \
{                                                                                     \
    XSValue::Status myStatus = XSValue::st_Init;                                      \
    XMLCh* actRetCanRep = XSValue::getCanonicalRepresentation(                        \
                                                  StrX(data).unicodeForm()            \
                                                , datatype                            \
                                                , myStatus                            \
                                                , XSValue::ver_10                     \
                                                , toValidate                          \
                                                , XMLPlatformUtils::fgMemoryManager); \
    if (actRetCanRep) {                                                               \
        if (!expRetCanRep) {                                                          \
            printf("CANREP_TEST CanRep returned:                                      \
                    at line <%d> data=<%s>, datatype=<%s>\n"                          \
                  , __LINE__, data, StrX(getDataTypeString(datatype)).localForm());   \
            XMLPlatformUtils::fgMemoryManager->deallocate(actRetCanRep);              \
            errSeen = true;                                                           \
        }                                                                             \
        else {                                                                        \
            char* actRetCanRep_inchar = XMLString::transcode(actRetCanRep);           \
            if (!XMLString::equals(actRetCanRep_inchar, toCompare)) {                 \
                printf("CANREP_TEST CanRep Diff                                       \
                  , at line <%d> data=<%s>, datatype=<%s>,                            \
                    actCanRep=<%s>, toCompare=<%s>\n"                                 \
                  , __LINE__, data, StrX(getDataTypeString(datatype)).localForm()     \
                  , actRetCanRep_inchar, toCompare);                                  \
                errSeen = true;                                                       \
            }                                                                         \
            XMLPlatformUtils::fgMemoryManager->deallocate(actRetCanRep);              \
            XMLString::release(&actRetCanRep_inchar);                                 \
        }                                                                             \
    }                                                                                 \
    else {                                                                            \
        if (expRetCanRep){                                                            \
            printf("CANREP_TEST No CanRep returned,                                   \
                    at line <%d> data=<%s>, datatype=<%s>\n"                          \
                  , __LINE__, data, StrX(getDataTypeString(datatype)).localForm());   \
            errSeen = true;                                                           \
        }                                                                             \
        else {                                                                        \
        if (expStatus != myStatus) {                                                  \
                printf("CANREP_TEST Context Diff,                                     \
                        at line <%d> data=<%s>, datatype=<%d>\n                       \
                        expStatus=<%s>, actStatus=<%s>\n"                             \
                      , __LINE__, data, datatype                                      \
                      , getStatusString(expStatus), getStatusString(myStatus));       \
                errSeen = true;                                                       \
            }                                                                         \
        }                                                                             \
    }                                                                                 \
}    
#endif

#ifdef _DEBUG
void DATATYPE_TEST( const XMLCh*             const  dt_String
                  , const XSValue::DataType         expDataType
                  )
{
    XSValue::DataType actDataType = XSValue::getDataType(dt_String);

    if (actDataType != expDataType)
    {
        char* dt_str = XMLString::transcode(dt_String);
        printf("DATATYPE_TEST Fails: data=<%s>, actDataType=<%d>, expDataType=<%d>\n",
                dt_str, actDataType, expDataType);
        XMLString::release(&dt_str);
        errSeen = true;
    }
}
#else
#define DATATYPE_TEST(dt_String, expDataType)                                          \
{                                                                                      \
    XSValue::DataType actDataType = XSValue::getDataType(dt_String);                   \
    if (actDataType != expDataType)                                                    \
    {                                                                                  \
        char* dt_str = XMLString::transcode(dt_String);                                \
        printf("DATATYPE_TEST Fails: data=<%s>, actDataType=<%d>, expDataType=<%d>\n", \
                dt_str, actDataType, expDataType);                                     \
        XMLString::release(&dt_str);                                                   \
        errSeen = true;                                                                \
    }                                                                                  \
}
#endif

void  testNoActVal(const char*                  const  data
                 , const XSValue::DataType             datatype
                 , const XSValue::Status               expStatus)
{
    XSValue::Status ret_Status = XSValue::st_Init;
    XSValue* actVal = XSValue::getActualValue(StrX(data).unicodeForm(), datatype, ret_Status);

    if (actVal)
    {
        printf("testNoActVal fails, data=<%s>\n", data);
        delete actVal;
        errSeen=true;
        return;
    }

    if (ret_Status != expStatus)
    {
        printf("testNoActVal fails, data=<%s> retStatus=<%s> expStatus=<%s>\n", 
                data
              , getStatusString(ret_Status)
              , getStatusString(expStatus));
        errSeen=true;
    }

}

void  testNoCanRep(const char*                  const  data
                 , const XSValue::DataType             datatype
                 , const XSValue::Status               expStatus)
{
    XSValue::Status ret_Status = XSValue::st_Init;
    XMLCh* canRep = XSValue::getCanonicalRepresentation(StrX(data).unicodeForm(), datatype, ret_Status);

    if (canRep)
    {
        printf("testNoCanRep fails, data=<%s>\n", data);
        delete canRep;
        errSeen=true;
        return;
    }

    if (ret_Status != expStatus)
    {
        printf("testNoCanRep fails, data=<%s> retStatus=<%s> expStatus=<%s>\n", 
                data
              , getStatusString(ret_Status)
              , getStatusString(expStatus));
        errSeen=true;
    }
}

/***
 *   Test cases
 ***/
void test_dt_decimal()
{
    const XSValue::DataType dt = XSValue::dt_decimal; 
    bool  toValidate = true;

    const char lex_v_ran_v_1[]="1234.567";
    const char lex_v_ran64_v_1[]="18446744073709551615.999";
    const char lex_v_ran64_v_2[]="999.18446744073709551615";
    const char lex_v_ran64_iv_1[]="18446744073709551616.999";
    const char lex_v_ran64_iv_2[]="999.18446744073709551616";

    const char lex_v_ran32_v_1[]="4294967295.999";
    const char lex_v_ran32_v_2[]="999.4294967295";
    const char lex_v_ran32_iv_1[]="4294967296.999";
    const char lex_v_ran32_iv_2[]="999.4294967296";

    const char lex_iv_1[]="12b34.456";
    const char lex_iv_2[]="1234.56.789";

/***
 * 3.2.3.2 Canonical representation
 *
 * The canonical representation for decimal is defined by prohibiting certain options from the Lexical 
 * representation (�3.2.3.1). Specifically, 
 * 1. the preceding optional "+" sign is prohibited. 
 * 2. The decimal point is required. 
 * 3. Leading and trailing zeroes are prohibited subject to the following: 
 *       there must be at least one digit to the right and 
 *       to the left of the decimal point which may be a zero.
 ***/

    const char data_rawstr_1[]="-123.45";
    const char data_canrep_1[]="-123.45";
    const char data_rawstr_2[]="+123.45";
    const char data_canrep_2[]="123.45";
    const char data_rawstr_3[]="12345";
    const char data_canrep_3[]="12345.0";
    const char data_rawstr_4[]="000123.45";
    const char data_canrep_4[]="123.45";
    const char data_rawstr_5[]="123.45000";
    const char data_canrep_5[]="123.45";
    const char data_rawstr_6[]="00.12345";
    const char data_canrep_6[]="0.12345";
    const char data_rawstr_7[]="123.00";
    const char data_canrep_7[]="123.0";
   
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *    lexical valid          
     *            range  valid                           true              n/a
     *            range  invalid       n/a   
     *    lexical invalid                                false           st_FOCA0002
     * 
     ***/

    // lexical valid
    VALIDATE_TEST(lex_v_ran_v_1    , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran64_v_1  , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran64_v_2  , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran64_iv_1 , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran64_iv_2 , dt, EXP_RET_VALID_TRUE, DONT_CARE);

    // lexical invalid
    VALIDATE_TEST(lex_iv_1         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_iv_2         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        ACTVALUE_TEST(lex_v_ran_v_1,    dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

#if defined(XML_BITSTOBUILD_64)
        ACTVALUE_TEST(lex_v_ran64_v_1 , dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE); 
        ACTVALUE_TEST(lex_v_ran64_v_2 , dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        //ACTVALUE_TEST(lex_v_ran64_iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0001);
        //ACTVALUE_TEST(lex_v_ran64_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0001);
#else
        ACTVALUE_TEST(lex_v_ran32_v_1,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran32_v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        //ACTVALUE_TEST(lex_v_ran32_iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0001);
        //ACTVALUE_TEST(lex_v_ran32_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0001);
#endif

        ACTVALUE_TEST(lex_iv_1,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_iv_2,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XMLCh          n/a
     *          range  invalid          n/a                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XMLCh         n/a
     *          range  invalid          n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j)? true : false;

        CANREP_TEST(data_rawstr_1,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_1,    DONT_CARE);
        CANREP_TEST(data_rawstr_2,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_2,    DONT_CARE);
        CANREP_TEST(data_rawstr_3,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_3,    DONT_CARE);
        CANREP_TEST(data_rawstr_4,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_4,    DONT_CARE);
        CANREP_TEST(data_rawstr_5,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_5,    DONT_CARE);
        CANREP_TEST(data_rawstr_6,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_6,    DONT_CARE);
        CANREP_TEST(data_rawstr_7,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_7,    DONT_CARE);

        CANREP_TEST(lex_v_ran64_v_1,  dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran64_v_1,  DONT_CARE);
        CANREP_TEST(lex_v_ran64_v_2,  dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran64_v_2,  DONT_CARE);
        CANREP_TEST(lex_v_ran64_iv_1, dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran64_iv_1, DONT_CARE);
        CANREP_TEST(lex_v_ran64_iv_2, dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran64_iv_2, DONT_CARE);
        CANREP_TEST(lex_iv_1        , dt, toValidate, EXP_RET_CANREP_FALSE, 0,                XSValue::st_FOCA0002);
        CANREP_TEST(lex_iv_2        , dt, toValidate, EXP_RET_CANREP_FALSE, 0,                XSValue::st_FOCA0002);

    }

}

/***
  * FLT_EPSILON 1.192092896e-07F 
  * FLT_MIN 1.175494351e-38F 
  * FLT_MAX 3.402823466e+38F 
***/

void test_dt_float()
{

    const XSValue::DataType dt = XSValue::dt_float; 
    bool  toValidate = true;

    const char lex_v_ran_v_0[]="1234.e+10";
    const char lex_v_ran_v_1[]="+3.402823466e+38";
    const char lex_v_ran_v_2[]="-3.402823466e+38";
    const char lex_v_ran_v_3[]="+1.175494351e-38";
    const char lex_v_ran_v_4[]="-1.175494351e-38";

    const char lex_v_ran_iv_1[]="+3.402823466e+39";
    const char lex_v_ran_iv_2[]="-3.402823466e+39";
    const char lex_v_ran_iv_3[]="+1.175494351e-39";
    const char lex_v_ran_iv_4[]="-1.175494351e-39";

    const char lex_v_ran_iv_1_canrep[]="3.402823466E39";
    const char lex_v_ran_iv_2_canrep[]="-3.402823466E39";
    const char lex_v_ran_iv_3_canrep[]="1.175494351E-39";
    const char lex_v_ran_iv_4_canrep[]="-1.175494351E-39";

    const char lex_iv_1[]="12x.e+10";
    const char lex_iv_2[]="12.e+1x";

/***
 * 3.2.4.2 Canonical representation
 *
 * The canonical representation for float is defined by prohibiting certain options from the Lexical 
 * representation (�3.2.4.1). 
 * Specifically, 
 * 1. the exponent must be indicated by "E". 
 * 2. Leading zeroes and the preceding optional "+" sign are prohibited in the exponent. 
 * 3. For the mantissa, the preceding optional "+" sign is prohibited and the decimal point is required. 
 *    Leading and trailing zeroes are prohibited subject to the following: 
 *    number representations must be normalized such that there is a single digit to the left of the decimal point
 *    and at least a single digit to the right of the decimal point.
 *
 ***/

    const char data_rawstr_1[]="-123.45";
    const char data_canrep_1[]="-1.2345E2";
    const char data_rawstr_2[]="+123.45";
    const char data_canrep_2[]="1.2345E2";
    const char data_rawstr_3[]="+123.45e+0012";
    const char data_canrep_3[]="1.2345E14";
    const char data_rawstr_4[]="+100.000e2";
    const char data_canrep_4[]="1.0E4";
    const char data_rawstr_5[]="00100.23e2";
    const char data_canrep_5[]="1.0023E4";

    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *    lexical valid          
     *            range  valid                           true              n/a
     *            range  invalid                         false           st_FOCA0002   
     *    lexical invalid                                false           st_FOCA0002
     * 
     ***/

    // lexical valid, range valid
    VALIDATE_TEST(lex_v_ran_v_0 , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran_v_1 , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran_v_2 , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran_v_3 , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran_v_4 , dt, EXP_RET_VALID_TRUE, DONT_CARE);

    // lexical valid, range invalid
    VALIDATE_TEST(lex_v_ran_iv_1 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_v_ran_iv_2 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_v_ran_iv_3 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_v_ran_iv_4 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    // lexical invalid
    VALIDATE_TEST(lex_iv_1         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_iv_2         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/

    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        // lexical valid, range valid
        ACTVALUE_TEST(lex_v_ran_v_0,  dt, toValidate, EXP_RET_VALUE_TRUE, DONT_CARE);
        ACTVALUE_TEST(lex_v_ran_v_1,  dt, toValidate, EXP_RET_VALUE_TRUE, DONT_CARE);
        ACTVALUE_TEST(lex_v_ran_v_2,  dt, toValidate, EXP_RET_VALUE_TRUE, DONT_CARE);
        ACTVALUE_TEST(lex_v_ran_v_3,  dt, toValidate, EXP_RET_VALUE_TRUE, DONT_CARE);
        ACTVALUE_TEST(lex_v_ran_v_4,  dt, toValidate, EXP_RET_VALUE_TRUE, DONT_CARE);

        // lexical valid, range invalid
        ACTVALUE_TEST(lex_v_ran_iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_v_ran_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_v_ran_iv_3, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_v_ran_iv_4, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);

        // lexical invalid
        ACTVALUE_TEST(lex_iv_1      , dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_iv_2      , dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);

    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XMLCh          n/a
     *          range  invalid                              0            st_FOCA0002
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XMLCh          n/a
     *          range  invalid                            XMLCh          n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        // lexical valid, range valid
        CANREP_TEST(data_rawstr_1,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_1,    DONT_CARE);
        CANREP_TEST(data_rawstr_2,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_2,    DONT_CARE);
        CANREP_TEST(data_rawstr_3,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_3,    DONT_CARE);
        CANREP_TEST(data_rawstr_4,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_4,    DONT_CARE);
        CANREP_TEST(data_rawstr_5,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_5,    DONT_CARE);

        // lexical invalid
        CANREP_TEST(lex_iv_1,         dt, toValidate, EXP_RET_CANREP_FALSE,  0,               XSValue::st_FOCA0002);
        CANREP_TEST(lex_iv_2,         dt, toValidate, EXP_RET_CANREP_FALSE,  0,               XSValue::st_FOCA0002);
    }

    // lexical valid, range invalid

    toValidate = true;
    CANREP_TEST(lex_v_ran_iv_1,    dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);
    CANREP_TEST(lex_v_ran_iv_2,    dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);
    CANREP_TEST(lex_v_ran_iv_3,    dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);
    CANREP_TEST(lex_v_ran_iv_4,    dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);

    toValidate = false;
    CANREP_TEST(lex_v_ran_iv_1,    dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran_iv_1_canrep,    DONT_CARE);
    CANREP_TEST(lex_v_ran_iv_2,    dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran_iv_2_canrep,    DONT_CARE);
    CANREP_TEST(lex_v_ran_iv_3,    dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran_iv_3_canrep,    DONT_CARE);
    CANREP_TEST(lex_v_ran_iv_4,    dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran_iv_4_canrep,    DONT_CARE);

}

/***
DBL_EPSILON 2.2204460492503131e-016
DBL_MAX 1.7976931348623158e+308
DBL_MIN 2.2250738585072014e-308 
***/
void test_dt_double()
{

    const XSValue::DataType dt = XSValue::dt_double; 
    bool  toValidate = true;

    const char lex_v_ran_v_0[]="1234.e+10";
    const char lex_v_ran_v_1[]="+1.7976931348623158e+308";
    const char lex_v_ran_v_2[]="-1.7976931348623158e+308";
    const char lex_v_ran_v_3[]="+2.2250738585072014e-308";
    const char lex_v_ran_v_4[]="-2.2250738585072014e-308";

    const char lex_v_ran_iv_1[]="+1.7976931348623158e+309";
    const char lex_v_ran_iv_2[]="-1.7976931348623158e+309";
    // on linux, hp, aix, the representable range is around e-324
    // or e-325, using e-329 to gain consistent result on all
    // platforms
    const char lex_v_ran_iv_3[]="+2.2250738585072014e-329";
    const char lex_v_ran_iv_4[]="-2.2250738585072014e-329";

    const char lex_v_ran_iv_1_canrep[]="1.7976931348623158E309";
    const char lex_v_ran_iv_2_canrep[]="-1.7976931348623158E309";
    const char lex_v_ran_iv_3_canrep[]="2.2250738585072014E-329";
    const char lex_v_ran_iv_4_canrep[]="-2.2250738585072014E-329";

    const char lex_iv_1[]="12x.e+10";
    const char lex_iv_2[]="12.e+1x";

/***
 * 3.2.5.2 Canonical representation
 *
 * The canonical representation for float is defined by prohibiting certain options from the Lexical 
 * representation (�3.2.5.1). 
 * Specifically, 
 * 1. the exponent must be indicated by "E". 
 * 2. Leading zeroes and the preceding optional "+" sign are prohibited in the exponent. 
 * 3. For the mantissa, the preceding optional "+" sign is prohibited and the decimal point is required. 
 *    Leading and trailing zeroes are prohibited subject to the following: 
 *    number representations must be normalized such that there is a single digit to the left of the decimal point
 *    and at least a single digit to the right of the decimal point.
 *
 ***/

    const char data_rawstr_1[]="-123.45";
    const char data_canrep_1[]="-1.2345E2";
    const char data_rawstr_2[]="+123.45";
    const char data_canrep_2[]="1.2345E2";
    const char data_rawstr_3[]="+123.45e+0012";
    const char data_canrep_3[]="1.2345E14";
    const char data_rawstr_4[]="+100.000e2";
    const char data_canrep_4[]="1.0E4";
    const char data_rawstr_5[]="00100.23e2";
    const char data_canrep_5[]="1.0023E4";

    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *    lexical valid          
     *            range  valid                           true              n/a
     *            range  invalid                         false           st_FOCA0002   
     *    lexical invalid                                false           st_FOCA0002
     * 
     ***/

    // lexical valid, range valid
    VALIDATE_TEST(lex_v_ran_v_0 , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran_v_1 , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran_v_2 , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran_v_3 , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran_v_4 , dt, EXP_RET_VALID_TRUE, DONT_CARE);

    // lexical valid, range invalid
    VALIDATE_TEST(lex_v_ran_iv_1 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_v_ran_iv_2 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_v_ran_iv_3 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_v_ran_iv_4 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    // lexical invalid
    VALIDATE_TEST(lex_iv_1         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_iv_2         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/

    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        // lexical valid, range valid
        ACTVALUE_TEST(lex_v_ran_v_0,  dt, toValidate, EXP_RET_VALUE_TRUE, DONT_CARE);
        ACTVALUE_TEST(lex_v_ran_v_1,  dt, toValidate, EXP_RET_VALUE_TRUE, DONT_CARE);
        ACTVALUE_TEST(lex_v_ran_v_2,  dt, toValidate, EXP_RET_VALUE_TRUE, DONT_CARE);
        ACTVALUE_TEST(lex_v_ran_v_3,  dt, toValidate, EXP_RET_VALUE_TRUE, DONT_CARE);
        ACTVALUE_TEST(lex_v_ran_v_4,  dt, toValidate, EXP_RET_VALUE_TRUE, DONT_CARE);

        // lexical valid, range invalid
        ACTVALUE_TEST(lex_v_ran_iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_v_ran_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_v_ran_iv_3, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_v_ran_iv_4, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);

        // lexical invalid
        ACTVALUE_TEST(lex_iv_1      , dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_iv_2      , dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);

    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XMLCh          n/a
     *          range  invalid                              0            st_FOCA0002
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XMLCh          n/a
     *          range  invalid                            XMLCh          n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        // lexical valid, range valid
        CANREP_TEST(data_rawstr_1,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_1,    DONT_CARE);
        CANREP_TEST(data_rawstr_2,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_2,    DONT_CARE);
        CANREP_TEST(data_rawstr_3,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_3,    DONT_CARE);
        CANREP_TEST(data_rawstr_4,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_4,    DONT_CARE);
        CANREP_TEST(data_rawstr_5,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_5,    DONT_CARE);

        // lexical invalid
        CANREP_TEST(lex_iv_1,         dt, toValidate, EXP_RET_CANREP_FALSE,  0,               XSValue::st_FOCA0002);
        CANREP_TEST(lex_iv_2,         dt, toValidate, EXP_RET_CANREP_FALSE,  0,               XSValue::st_FOCA0002);
    }

    // lexical valid, range invalid

    toValidate = true;
    CANREP_TEST(lex_v_ran_iv_1,    dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);
    CANREP_TEST(lex_v_ran_iv_2,    dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);
    CANREP_TEST(lex_v_ran_iv_3,    dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);
    CANREP_TEST(lex_v_ran_iv_4,    dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);

    toValidate = false;
    CANREP_TEST(lex_v_ran_iv_1,    dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran_iv_1_canrep,    DONT_CARE);
    CANREP_TEST(lex_v_ran_iv_2,    dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran_iv_2_canrep,    DONT_CARE);
    CANREP_TEST(lex_v_ran_iv_3,    dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran_iv_3_canrep,    DONT_CARE);
    CANREP_TEST(lex_v_ran_iv_4,    dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran_iv_4_canrep,    DONT_CARE);

}

/***
 *  9223372036854775807 
 * -9223372036854775808
 *  2147483647 
 * -2147483648
 ***/

void test_dt_integer()
{
    const XSValue::DataType dt = XSValue::dt_integer; 
    bool  toValidate = true;

    const char lex_v_ran_v_1[]="1234";
    const char lex_v_ran64_v_1[]="+9223372036854775807";
    const char lex_v_ran64_v_2[]="-9223372036854775808";
    const char lex_v_ran64_iv_1[]="+9223372036854775808";
    const char lex_v_ran64_iv_2[]="-9223372036854775809";

    const char lex_v_ran32_v_1[]="+2147483647";
    const char lex_v_ran32_v_2[]="-2147483648";
    const char lex_v_ran32_iv_1[]="+2147483648";
    const char lex_v_ran32_iv_2[]="-2147483649";

    const char lex_v_ran64_v_1_canrep[]="9223372036854775807";
    const char lex_v_ran64_v_2_canrep[]="-9223372036854775808";
    const char lex_v_ran64_iv_1_canrep[]="9223372036854775808";
    const char lex_v_ran64_iv_2_canrep[]="-9223372036854775809";

    const char lex_iv_1[]="12b34.456";
    const char lex_iv_2[]="1234b56";

/***
 * 3.3.13.2 Canonical representation
 *
 * The canonical representation for integer is defined by prohibiting certain options from the Lexical 
 * representation (�3.3.13.1). Specifically, 
 * 1. the preceding optional "+" sign is prohibited and 
 * 2. leading zeroes are prohibited.
 *
 ***/

    const char data_rawstr_1[]="+12345";
    const char data_canrep_1[]="12345";
    const char data_rawstr_2[]="00012345";
    const char data_canrep_2[]="12345";
   
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *    lexical valid          
     *            range  valid                           true              n/a
     *            range  invalid       n/a   
     *    lexical invalid                                false           st_FOCA0002
     * 
     ***/

    // lexical valid
    VALIDATE_TEST(lex_v_ran_v_1    , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran64_v_1  , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran64_v_2  , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran64_iv_1 , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran64_iv_2 , dt, EXP_RET_VALID_TRUE, DONT_CARE);

    // lexical invalid
    VALIDATE_TEST(lex_iv_1         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_iv_2         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        ACTVALUE_TEST(lex_v_ran_v_1,    dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

#if defined(XML_BITSTOBUILD_64)
        ACTVALUE_TEST(lex_v_ran64_v_1 , dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE); 
        ACTVALUE_TEST(lex_v_ran64_v_2 , dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran64_iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0003);
        ACTVALUE_TEST(lex_v_ran64_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0003);
#else
        ACTVALUE_TEST(lex_v_ran32_v_1,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran32_v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran32_iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0003);
        ACTVALUE_TEST(lex_v_ran32_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0003);
#endif

        ACTVALUE_TEST(lex_iv_1,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_iv_2,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XMLCh          n/a
     *          range  invalid          n/a                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XMLCh         n/a
     *          range  invalid          n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j)? true : false;

        CANREP_TEST(data_rawstr_1,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_1,    DONT_CARE);
        CANREP_TEST(data_rawstr_2,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_2,    XSValue::st_FOCA0002);

        CANREP_TEST(lex_v_ran64_v_1,  dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran64_v_1_canrep,  DONT_CARE);
        CANREP_TEST(lex_v_ran64_v_2,  dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran64_v_2_canrep,  DONT_CARE);
        CANREP_TEST(lex_v_ran64_iv_1, dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran64_iv_1_canrep, DONT_CARE);
        CANREP_TEST(lex_v_ran64_iv_2, dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran64_iv_2_canrep, DONT_CARE);
        CANREP_TEST(lex_iv_1        , dt, toValidate, EXP_RET_CANREP_FALSE, 0,                XSValue::st_FOCA0002);
        CANREP_TEST(lex_iv_2        , dt, toValidate, EXP_RET_CANREP_FALSE, 0,                XSValue::st_FOCA0002);

    }

}

void test_dt_nonPositiveInteger()
{
    const XSValue::DataType dt = XSValue::dt_nonPositiveInteger; 
    bool  toValidate = true;

    const char lex_v_ran_v_1[]="-1234";
    const char lex_v_ran_iv_1[]="+1";

    const char lex_v_ran64_v_2[]="-9223372036854775808";
    const char lex_v_ran64_iv_2[]="-9223372036854775809";

    const char lex_v_ran32_v_2[]="-2147483648";
    const char lex_v_ran32_iv_2[]="-2147483649";

    const char lex_v_ran64_v_2_canrep[]="-9223372036854775808";
    const char lex_v_ran64_iv_2_canrep[]="-9223372036854775809";

    const char lex_iv_1[]="12b34.456";
    const char lex_iv_2[]="1234b56";


/***
 * 3.3.14.2 Canonical representation
 *
 * The canonical representation for nonPositiveInteger is defined by prohibiting certain options from the 
 * Lexical representation (�3.3.14.1). Specifically, 
 * 1. the negative sign ("-") is required with the token "0" and 
 * 2. leading zeroes are prohibited.
 *
 ***/

    const char data_rawstr_1[]="0";
    const char data_canrep_1[]="-0";
    const char data_rawstr_2[]="-00012345";
    const char data_canrep_2[]="-12345";
   
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *    lexical valid          
     *            range  valid                           true              n/a
     *            range  invalid       n/a   
     *    lexical invalid                                false           st_FOCA0002
     * 
     ***/

    // lexical valid
    VALIDATE_TEST(lex_v_ran_v_1    , dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(lex_v_ran_iv_1   , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    VALIDATE_TEST(lex_v_ran64_v_2  , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran64_iv_2 , dt, EXP_RET_VALID_TRUE, DONT_CARE);

    // lexical invalid
    VALIDATE_TEST(lex_iv_1         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_iv_2         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        ACTVALUE_TEST(lex_v_ran_v_1,    dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

#if defined(XML_BITSTOBUILD_64)
        ACTVALUE_TEST(lex_v_ran64_v_2 , dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran64_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0003);
#else
        ACTVALUE_TEST(lex_v_ran32_v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran32_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0003);
#endif

        ACTVALUE_TEST(lex_iv_1,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_iv_2,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XMLCh          n/a
     *          range  invalid          n/a                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XMLCh         n/a
     *          range  invalid          n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j)? true : false;

        CANREP_TEST(data_rawstr_1,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_1,    DONT_CARE);
        CANREP_TEST(data_rawstr_2,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_2,    DONT_CARE);

        CANREP_TEST(lex_v_ran64_v_2,  dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran64_v_2_canrep,  DONT_CARE);
        CANREP_TEST(lex_v_ran64_iv_2, dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran64_iv_2_canrep, DONT_CARE);
        CANREP_TEST(lex_iv_1        , dt, toValidate, EXP_RET_CANREP_FALSE, 0,                XSValue::st_FOCA0002);
        CANREP_TEST(lex_iv_2        , dt, toValidate, EXP_RET_CANREP_FALSE, 0,                XSValue::st_FOCA0002);

    }

}

void test_dt_negativeInteger()
{
    const XSValue::DataType dt = XSValue::dt_negativeInteger; 
    bool  toValidate = true;

    const char lex_v_ran_v_1[]="-1234";
    const char lex_v_ran_iv_1[]="0";

    const char lex_v_ran64_v_2[]="-9223372036854775808";
    const char lex_v_ran64_iv_2[]="-9223372036854775809";

    const char lex_v_ran32_v_2[]="-2147483648";
    const char lex_v_ran32_iv_2[]="-2147483649";

    const char lex_v_ran64_v_2_canrep[]="-9223372036854775808";
    const char lex_v_ran64_iv_2_canrep[]="-9223372036854775809";

    const char lex_iv_1[]="12b34.456";
    const char lex_iv_2[]="1234b56";


/***
 * 3.3.15.2 Canonical representation
 *
 * The canonical representation for negativeInteger is defined by prohibiting certain options 
 * from the Lexical representation (�3.3.15.1). Specifically, 
 * 1. leading zeroes are prohibited.
 *
 ***/

    const char data_rawstr_1[]="-00012345";
    const char data_canrep_1[]="-12345";
   
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *    lexical valid          
     *            range  valid                           true              n/a
     *            range  invalid       n/a   
     *    lexical invalid                                false           st_FOCA0002
     * 
     ***/

    // lexical valid
    VALIDATE_TEST(lex_v_ran_v_1    , dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(lex_v_ran_iv_1   , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    VALIDATE_TEST(lex_v_ran64_v_2  , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran64_iv_2 , dt, EXP_RET_VALID_TRUE, DONT_CARE);

    // lexical invalid
    VALIDATE_TEST(lex_iv_1         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_iv_2         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        ACTVALUE_TEST(lex_v_ran_v_1,    dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

#if defined(XML_BITSTOBUILD_64)
        ACTVALUE_TEST(lex_v_ran64_v_2 , dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran64_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0003);
#else
        ACTVALUE_TEST(lex_v_ran32_v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran32_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0003);
#endif

        ACTVALUE_TEST(lex_iv_1,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_iv_2,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XMLCh          n/a
     *          range  invalid          n/a                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XMLCh         n/a
     *          range  invalid          n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j)? true : false;

        CANREP_TEST(data_rawstr_1,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_1,    DONT_CARE);

        CANREP_TEST(lex_v_ran64_v_2,  dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran64_v_2_canrep,  DONT_CARE);
        CANREP_TEST(lex_v_ran64_iv_2, dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran64_iv_2_canrep, DONT_CARE);
        CANREP_TEST(lex_iv_1        , dt, toValidate, EXP_RET_CANREP_FALSE, 0,                XSValue::st_FOCA0002);
        CANREP_TEST(lex_iv_2        , dt, toValidate, EXP_RET_CANREP_FALSE, 0,                XSValue::st_FOCA0002);

    }

}

void test_dt_long()
{
    const XSValue::DataType dt = XSValue::dt_long; 
    bool  toValidate = true;

    const char lex_v_ran_v_1[]="1234";
    const char lex_v_ran64_v_1[]="+9223372036854775807";
    const char lex_v_ran64_v_2[]="-9223372036854775808";
    const char lex_v_ran64_iv_1[]="+9223372036854775808";
    const char lex_v_ran64_iv_2[]="-9223372036854775809";

    const char lex_v_ran32_v_1[]="+2147483647";
    const char lex_v_ran32_v_2[]="-2147483648";
    const char lex_v_ran32_iv_1[]="+2147483648";
    const char lex_v_ran32_iv_2[]="-2147483649";

    const char lex_v_ran64_v_1_canrep[]="9223372036854775807";
    const char lex_v_ran64_v_2_canrep[]="-9223372036854775808";
    const char lex_v_ran64_iv_1_canrep[]="9223372036854775808";
    const char lex_v_ran64_iv_2_canrep[]="-9223372036854775809";

    const char lex_iv_1[]="12b34.456";
    const char lex_iv_2[]="1234b56";

/***
 * 3.3.16.2 Canonical representation
 *
 * The canonical representation for long is defined by prohibiting certain options from the 
 * Lexical representation (�3.3.16.1). Specifically, 
 * 1. the the optional "+" sign is prohibited and 
 * 2. leading zeroes are prohibited.

 ***/

    const char data_rawstr_1[]="+12345";
    const char data_canrep_1[]="12345";
    const char data_rawstr_2[]="00012345";
    const char data_canrep_2[]="12345";
   
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *    lexical valid          
     *            range  valid                           true              n/a
     *            range  invalid                         false           st_FOCA0002   
     *    lexical invalid                                false           st_FOCA0002
     * 
     ***/

    // lexical valid, valid range
    VALIDATE_TEST(lex_v_ran_v_1    , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran64_v_1  , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran64_v_2  , dt, EXP_RET_VALID_TRUE, DONT_CARE);

    // lexical valid, invalid range
    VALIDATE_TEST(lex_v_ran64_iv_1 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_v_ran64_iv_2 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    // lexical invalid
    VALIDATE_TEST(lex_iv_1         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_iv_2         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        ACTVALUE_TEST(lex_v_ran_v_1,    dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

#if defined(XML_BITSTOBUILD_64)
        ACTVALUE_TEST(lex_v_ran64_v_1 , dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE); 
        ACTVALUE_TEST(lex_v_ran64_v_2 , dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran64_iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0003);
        ACTVALUE_TEST(lex_v_ran64_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0003);
#else
        ACTVALUE_TEST(lex_v_ran32_v_1,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran32_v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran32_iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0003);
        ACTVALUE_TEST(lex_v_ran32_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0003);
#endif

        ACTVALUE_TEST(lex_iv_1,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_iv_2,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XMLCh          n/a
     *          range  invalid                              0            st_FOCA0002
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XMLCh         n/a
     *          range  invalid                            XMLCh         n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j)? true : false;

        CANREP_TEST(data_rawstr_1,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_1,    DONT_CARE);
        CANREP_TEST(data_rawstr_2,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_2,    XSValue::st_FOCA0002);

        CANREP_TEST(lex_v_ran64_v_1,  dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran64_v_1_canrep,  DONT_CARE);
        CANREP_TEST(lex_v_ran64_v_2,  dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran64_v_2_canrep,  DONT_CARE);

        CANREP_TEST(lex_iv_1        , dt, toValidate, EXP_RET_CANREP_FALSE, 0,                XSValue::st_FOCA0002);
        CANREP_TEST(lex_iv_2        , dt, toValidate, EXP_RET_CANREP_FALSE, 0,                XSValue::st_FOCA0002);

    }

    //validation on
    CANREP_TEST(lex_v_ran64_iv_1, dt, true,  EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);
    CANREP_TEST(lex_v_ran64_iv_2, dt, true,  EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);

    //validation off
    CANREP_TEST(lex_v_ran64_iv_1, dt, false, EXP_RET_CANREP_TRUE,  lex_v_ran64_iv_1_canrep, DONT_CARE);
    CANREP_TEST(lex_v_ran64_iv_2, dt, false, EXP_RET_CANREP_TRUE,  lex_v_ran64_iv_2_canrep, DONT_CARE);
}

void test_dt_int()
{
    const XSValue::DataType dt = XSValue::dt_int; 
    bool  toValidate = true;

    const char lex_v_ran_v_0[]="1234";

    const char lex_v_ran_v_1[]="+2147483647";
    const char lex_v_ran_v_2[]="-2147483648";
    const char lex_v_ran_iv_1[]="+2147483648";
    const char lex_v_ran_iv_2[]="-2147483649";

    const char lex_v_ran_v_1_canrep[]="2147483647";
    const char lex_v_ran_v_2_canrep[]="-2147483648";
    const char lex_v_ran_iv_1_canrep[]="2147483648";
    const char lex_v_ran_iv_2_canrep[]="-2147483649";

    const char lex_iv_1[]="1234.456";
    const char lex_iv_2[]="1234b56";

/***
 * 3.3.17.2 Canonical representation
 *
 * The canonical representation for int is defined by prohibiting certain options from the 
 * Lexical representation (�3.3.17.1). Specifically, 
 * 1. the the optional "+" sign is prohibited and 
 * 2. leading zeroes are prohibited.
 *
 ***/

    const char data_rawstr_1[]="+12345";
    const char data_canrep_1[]="12345";
    const char data_rawstr_2[]="00012345";
    const char data_canrep_2[]="12345";
   
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *    lexical valid          
     *            range  valid                           true              n/a
     *            range  invalid                         false           st_FOCA0002   
     *    lexical invalid                                false           st_FOCA0002
     * 
     ***/

    // lexical valid, valid range
    VALIDATE_TEST(lex_v_ran_v_0  , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran_v_1  , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran_v_2  , dt, EXP_RET_VALID_TRUE, DONT_CARE);

    // lexical valid, invalid range
    VALIDATE_TEST(lex_v_ran_iv_1 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_v_ran_iv_2 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    // lexical invalid
    VALIDATE_TEST(lex_iv_1         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_iv_2         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        ACTVALUE_TEST(lex_v_ran_v_1,    dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

        ACTVALUE_TEST(lex_v_ran_v_1,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran_v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran_iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_v_ran_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);

        ACTVALUE_TEST(lex_iv_1,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_iv_2,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XMLCh          n/a
     *          range  invalid                              0            st_FOCA0002
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XMLCh         n/a
     *          range  invalid                            XMLCh         n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j)? true : false;

        CANREP_TEST(data_rawstr_1, dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_1,        DONT_CARE);
        CANREP_TEST(data_rawstr_2, dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_2,        XSValue::st_FOCA0002);

        CANREP_TEST(lex_v_ran_v_1, dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran_v_1_canrep, DONT_CARE);
        CANREP_TEST(lex_v_ran_v_2, dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran_v_2_canrep, DONT_CARE);

        CANREP_TEST(lex_iv_1,      dt, toValidate, EXP_RET_CANREP_FALSE, 0,                    XSValue::st_FOCA0002);
        CANREP_TEST(lex_iv_2,      dt, toValidate, EXP_RET_CANREP_FALSE, 0,                    XSValue::st_FOCA0002);

    }

    //validation on
    CANREP_TEST(lex_v_ran_iv_1, dt, true,  EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);
    CANREP_TEST(lex_v_ran_iv_2, dt, true,  EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);

    //validation off
    CANREP_TEST(lex_v_ran_iv_1, dt, false, EXP_RET_CANREP_TRUE,  lex_v_ran_iv_1_canrep, DONT_CARE);
    CANREP_TEST(lex_v_ran_iv_2, dt, false, EXP_RET_CANREP_TRUE,  lex_v_ran_iv_2_canrep, DONT_CARE);
}

// 32767 
// -32768

void test_dt_short()
{
    const XSValue::DataType dt = XSValue::dt_short; 
    bool  toValidate = true;

    const char lex_v_ran_v_0[]="1234";

    const char lex_v_ran_v_1[]="+32767";
    const char lex_v_ran_v_2[]="-32768";
    const char lex_v_ran_iv_1[]="+32768";
    const char lex_v_ran_iv_2[]="-32769";

    const char lex_v_ran_v_1_canrep[]="32767";
    const char lex_v_ran_v_2_canrep[]="-32768";
    const char lex_v_ran_iv_1_canrep[]="32768";
    const char lex_v_ran_iv_2_canrep[]="-32769";

    const char lex_iv_1[]="1234.456";
    const char lex_iv_2[]="1234b56";

/***
 *
 * 3.3.18.2 Canonical representation
 *
 * The canonical representation for short is defined by prohibiting certain options from the 
 * Lexical representation (�3.3.18.1). Specifically, 
 * 1. the the optional "+" sign is prohibited and 
 * 2. leading zeroes are prohibited.
 *
 ***/

    const char data_rawstr_1[]="+12345";
    const char data_canrep_1[]="12345";
    const char data_rawstr_2[]="00012345";
    const char data_canrep_2[]="12345";
   
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *    lexical valid          
     *            range  valid                           true              n/a
     *            range  invalid                         false           st_FOCA0002   
     *    lexical invalid                                false           st_FOCA0002
     * 
     ***/

    // lexical valid, valid range
    VALIDATE_TEST(lex_v_ran_v_0  , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran_v_1  , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran_v_2  , dt, EXP_RET_VALID_TRUE, DONT_CARE);

    // lexical valid, invalid range
    VALIDATE_TEST(lex_v_ran_iv_1 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_v_ran_iv_2 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    // lexical invalid
    VALIDATE_TEST(lex_iv_1         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_iv_2         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        ACTVALUE_TEST(lex_v_ran_v_1,    dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

        ACTVALUE_TEST(lex_v_ran_v_1,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran_v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran_iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_v_ran_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);

        ACTVALUE_TEST(lex_iv_1,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_iv_2,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XMLCh          n/a
     *          range  invalid                              0            st_FOCA0002
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XMLCh         n/a
     *          range  invalid                            XMLCh         n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j)? true : false;

        CANREP_TEST(data_rawstr_1, dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_1,        DONT_CARE);
        CANREP_TEST(data_rawstr_2, dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_2,        XSValue::st_FOCA0002);

        CANREP_TEST(lex_v_ran_v_1, dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran_v_1_canrep, DONT_CARE);
        CANREP_TEST(lex_v_ran_v_2, dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran_v_2_canrep, DONT_CARE);

        CANREP_TEST(lex_iv_1,      dt, toValidate, EXP_RET_CANREP_FALSE, 0,                    XSValue::st_FOCA0002);
        CANREP_TEST(lex_iv_2,      dt, toValidate, EXP_RET_CANREP_FALSE, 0,                    XSValue::st_FOCA0002);

    }

    //validation on
    CANREP_TEST(lex_v_ran_iv_1, dt, true,  EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);
    CANREP_TEST(lex_v_ran_iv_2, dt, true,  EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);

    //validation off
    CANREP_TEST(lex_v_ran_iv_1, dt, false, EXP_RET_CANREP_TRUE,  lex_v_ran_iv_1_canrep, DONT_CARE);
    CANREP_TEST(lex_v_ran_iv_2, dt, false, EXP_RET_CANREP_TRUE,  lex_v_ran_iv_2_canrep, DONT_CARE);
}

//127 
//-128

void test_dt_byte()
{
    const XSValue::DataType dt = XSValue::dt_byte; 
    bool  toValidate = true;

    const char lex_v_ran_v_0[]="12";

    const char lex_v_ran_v_1[]="+127";
    const char lex_v_ran_v_2[]="-128";
    const char lex_v_ran_iv_1[]="+128";
    const char lex_v_ran_iv_2[]="-129";

    const char lex_v_ran_v_1_canrep[]="127";
    const char lex_v_ran_v_2_canrep[]="-128";
    const char lex_v_ran_iv_1_canrep[]="128";
    const char lex_v_ran_iv_2_canrep[]="-129";

    const char lex_iv_1[]="1234.456";
    const char lex_iv_2[]="1234b56";

/***
 *
 * 3.3.19.2 Canonical representation
 *
 * The canonical representation for byte is defined by prohibiting certain options from the 
 * Lexical representation (�3.3.19.1). Specifically, 
 * 1. the the optional "+" sign is prohibited and 
 * 2. leading zeroes are prohibited.
 *
 ***/
  
    const char data_rawstr_1[]="+123";
    const char data_canrep_1[]="123";
    const char data_rawstr_2[]="000123";
    const char data_canrep_2[]="123";
   
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *    lexical valid          
     *            range  valid                           true              n/a
     *            range  invalid                         false           st_FOCA0002   
     *    lexical invalid                                false           st_FOCA0002
     * 
     ***/

    // lexical valid, valid range
    VALIDATE_TEST(lex_v_ran_v_0  , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran_v_1  , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran_v_2  , dt, EXP_RET_VALID_TRUE, DONT_CARE);

    // lexical valid, invalid range
    VALIDATE_TEST(lex_v_ran_iv_1 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_v_ran_iv_2 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    // lexical invalid
    VALIDATE_TEST(lex_iv_1         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_iv_2         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        ACTVALUE_TEST(lex_v_ran_v_1,    dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

        ACTVALUE_TEST(lex_v_ran_v_1,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran_v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran_iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_v_ran_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);

        ACTVALUE_TEST(lex_iv_1,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_iv_2,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XMLCh          n/a
     *          range  invalid                              0            st_FOCA0002
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XMLCh         n/a
     *          range  invalid                            XMLCh         n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j)? true : false;

        CANREP_TEST(data_rawstr_1, dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_1,        DONT_CARE);
        CANREP_TEST(data_rawstr_2, dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_2,        XSValue::st_FOCA0002);

        CANREP_TEST(lex_v_ran_v_1, dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran_v_1_canrep, DONT_CARE);
        CANREP_TEST(lex_v_ran_v_2, dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran_v_2_canrep, DONT_CARE);

        CANREP_TEST(lex_iv_1,      dt, toValidate, EXP_RET_CANREP_FALSE, 0,                    XSValue::st_FOCA0002);
        CANREP_TEST(lex_iv_2,      dt, toValidate, EXP_RET_CANREP_FALSE, 0,                    XSValue::st_FOCA0002);

    }

    //validation on
    CANREP_TEST(lex_v_ran_iv_1, dt, true,  EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);
    CANREP_TEST(lex_v_ran_iv_2, dt, true,  EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);

    //validation off
    CANREP_TEST(lex_v_ran_iv_1, dt, false, EXP_RET_CANREP_TRUE,  lex_v_ran_iv_1_canrep, DONT_CARE);
    CANREP_TEST(lex_v_ran_iv_2, dt, false, EXP_RET_CANREP_TRUE,  lex_v_ran_iv_2_canrep, DONT_CARE);
}

void test_dt_nonNegativeInteger()
{
    const XSValue::DataType dt = XSValue::dt_nonNegativeInteger; 
    bool  toValidate = true;

    const char lex_v_ran_v_1[]="1234";
    const char lex_v_ran_iv_1[]="-1";

    const char lex_v_ran64_v_2[]="+9223372036854775807";
    const char lex_v_ran64_iv_2[]="+9223372036854775808";

    const char lex_v_ran32_v_2[]="2147483647";
    const char lex_v_ran32_iv_2[]="2147483648";

    const char lex_v_ran64_v_2_canrep[]="9223372036854775807";
    const char lex_v_ran64_iv_2_canrep[]="9223372036854775808";

    const char lex_iv_1[]="12b34.456";
    const char lex_iv_2[]="1234b56";


/***
 * 3.3.20.2 Canonical representation
 *
 * The canonical representation for nonNegativeInteger is defined by prohibiting certain options from the 
 * Lexical representation (�3.3.20.1). Specifically, 
 * 1. the the optional "+" sign is prohibited and 
 * 2. leading zeroes are prohibited.
 *
 ***/

    const char data_rawstr_1[]="0";
    const char data_canrep_1[]="0";
    const char data_rawstr_2[]="+00012345";
    const char data_canrep_2[]="12345";
   
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *    lexical valid          
     *            range  valid                           true              n/a
     *            range  invalid       n/a   
     *    lexical invalid                                false           st_FOCA0002
     * 
     ***/

    // lexical valid
    VALIDATE_TEST(lex_v_ran_v_1    , dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(lex_v_ran_iv_1   , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    VALIDATE_TEST(lex_v_ran64_v_2  , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran64_iv_2 , dt, EXP_RET_VALID_TRUE, DONT_CARE);

    // lexical invalid
    VALIDATE_TEST(lex_iv_1         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_iv_2         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        ACTVALUE_TEST(lex_v_ran_v_1,    dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

#if defined(XML_BITSTOBUILD_64)
        ACTVALUE_TEST(lex_v_ran64_v_2 , dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran64_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0003);
#else
        ACTVALUE_TEST(lex_v_ran32_v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran32_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0003);
#endif

        ACTVALUE_TEST(lex_iv_1,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_iv_2,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XMLCh          n/a
     *          range  invalid          n/a                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XMLCh         n/a
     *          range  invalid          n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j)? true : false;

        CANREP_TEST(data_rawstr_1,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_1,    DONT_CARE);
        CANREP_TEST(data_rawstr_2,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_2,    DONT_CARE);

        CANREP_TEST(lex_v_ran64_v_2,  dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran64_v_2_canrep,  DONT_CARE);
        CANREP_TEST(lex_v_ran64_iv_2, dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran64_iv_2_canrep, DONT_CARE);
        CANREP_TEST(lex_iv_1        , dt, toValidate, EXP_RET_CANREP_FALSE, 0,                XSValue::st_FOCA0002);
        CANREP_TEST(lex_iv_2        , dt, toValidate, EXP_RET_CANREP_FALSE, 0,                XSValue::st_FOCA0002);

    }

}

//18446744073709551615
// 4294967295
void test_dt_unsignedLong()
{
    const XSValue::DataType dt = XSValue::dt_unsignedLong; 
    bool  toValidate = true;

    const char lex_v_ran_v_1[]="1234";
    const char lex_v_ran64_v_1[]="+18446744073709551615";
    const char lex_v_ran64_v_2[]="0";
    const char lex_v_ran64_iv_1[]="+18446744073709551616";
    const char lex_v_ran64_iv_2[]="-1";

    const char lex_v_ran32_v_1[]="+4294967295";
    const char lex_v_ran32_v_2[]="0";
    const char lex_v_ran32_iv_1[]="4294967296";
    const char lex_v_ran32_iv_2[]="-1";

    const char lex_v_ran64_v_1_canrep[]="18446744073709551615";
    const char lex_v_ran64_v_2_canrep[]="0";
    const char lex_v_ran64_iv_1_canrep[]="18446744073709551616";
    const char lex_v_ran64_iv_2_canrep[]="-1";

    const char lex_iv_1[]="12b34.456";
    const char lex_iv_2[]="1234b56";

/***
 * 3.3.16.2 Canonical representation
 *
 * The canonical representation for long is defined by prohibiting certain options from the 
 * Lexical representation (�3.3.16.1). Specifically, 
 * 1. the the optional "+" sign is prohibited and 
 * 2. leading zeroes are prohibited.

 ***/

    const char data_rawstr_1[]="+12345";
    const char data_canrep_1[]="12345";
    const char data_rawstr_2[]="00012345";
    const char data_canrep_2[]="12345";
   
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *    lexical valid          
     *            range  valid                           true              n/a
     *            range  invalid                         false           st_FOCA0002   
     *    lexical invalid                                false           st_FOCA0002
     * 
     ***/

    // lexical valid, valid range
    VALIDATE_TEST(lex_v_ran_v_1    , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran64_v_1  , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran64_v_2  , dt, EXP_RET_VALID_TRUE, DONT_CARE);

    // lexical valid, invalid range
    VALIDATE_TEST(lex_v_ran64_iv_1 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_v_ran64_iv_2 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    // lexical invalid
    VALIDATE_TEST(lex_iv_1         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_iv_2         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        ACTVALUE_TEST(lex_v_ran_v_1,    dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

#if defined(XML_BITSTOBUILD_64)
        ACTVALUE_TEST(lex_v_ran64_v_1 , dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE); 
        ACTVALUE_TEST(lex_v_ran64_v_2 , dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran64_iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0003);
        ACTVALUE_TEST(lex_v_ran64_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
#else
        ACTVALUE_TEST(lex_v_ran32_v_1,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran32_v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran32_iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0003);
        ACTVALUE_TEST(lex_v_ran32_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
#endif

        ACTVALUE_TEST(lex_iv_1,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_iv_2,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XMLCh          n/a
     *          range  invalid                              0            st_FOCA0002
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XMLCh         n/a
     *          range  invalid                            XMLCh         n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j)? true : false;

        CANREP_TEST(data_rawstr_1,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_1,    DONT_CARE);
        CANREP_TEST(data_rawstr_2,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_2,    XSValue::st_FOCA0002);

        CANREP_TEST(lex_v_ran64_v_1,  dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran64_v_1_canrep,  DONT_CARE);
        CANREP_TEST(lex_v_ran64_v_2,  dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran64_v_2_canrep,  DONT_CARE);

        CANREP_TEST(lex_iv_1        , dt, toValidate, EXP_RET_CANREP_FALSE, 0,                XSValue::st_FOCA0002);
        CANREP_TEST(lex_iv_2        , dt, toValidate, EXP_RET_CANREP_FALSE, 0,                XSValue::st_FOCA0002);

    }

    //validation on
    CANREP_TEST(lex_v_ran64_iv_1, dt, true,  EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);
    CANREP_TEST(lex_v_ran64_iv_2, dt, true,  EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);

    //validation off
    CANREP_TEST(lex_v_ran64_iv_1, dt, false, EXP_RET_CANREP_TRUE,  lex_v_ran64_iv_1_canrep, DONT_CARE);
    CANREP_TEST(lex_v_ran64_iv_2, dt, false, EXP_RET_CANREP_TRUE,  lex_v_ran64_iv_2_canrep, DONT_CARE);
}

//4294967295
void test_dt_unsignedInt()
{
    const XSValue::DataType dt = XSValue::dt_unsignedInt; 
    bool  toValidate = true;

    const char lex_v_ran_v_0[]="1234";

    const char lex_v_ran_v_1[]="+4294967295";
    const char lex_v_ran_v_2[]="0";
    const char lex_v_ran_iv_1[]="4294967296";
    const char lex_v_ran_iv_2[]="-1";

    const char lex_v_ran_v_1_canrep[]="4294967295";
    const char lex_v_ran_v_2_canrep[]="0";
    const char lex_v_ran_iv_1_canrep[]="4294967296";
    const char lex_v_ran_iv_2_canrep[]="-1";

    const char lex_iv_1[]="12b34.456";
    const char lex_iv_2[]="1234b56";

/***
 * 3.3.22.2 Canonical representation
 *
 * The canonical representation for unsignedInt is defined by prohibiting certain options from the 
 * Lexical representation (�3.3.22.1). Specifically, 
 * leading zeroes are prohibited.
 *
 ***/

    const char data_rawstr_1[]="+12345";
    const char data_canrep_1[]="12345";
    const char data_rawstr_2[]="00012345";
    const char data_canrep_2[]="12345";
   
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *    lexical valid          
     *            range  valid                           true              n/a
     *            range  invalid                         false           st_FOCA0002   
     *    lexical invalid                                false           st_FOCA0002
     * 
     ***/

    // lexical valid, valid range
    VALIDATE_TEST(lex_v_ran_v_0  , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran_v_1  , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran_v_2  , dt, EXP_RET_VALID_TRUE, DONT_CARE);

    // lexical valid, invalid range
    VALIDATE_TEST(lex_v_ran_iv_1 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_v_ran_iv_2 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    // lexical invalid
    VALIDATE_TEST(lex_iv_1         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_iv_2         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        ACTVALUE_TEST(lex_v_ran_v_0,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

        ACTVALUE_TEST(lex_v_ran_v_1,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran_v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran_iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_v_ran_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);

        ACTVALUE_TEST(lex_iv_1,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_iv_2,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XMLCh          n/a
     *          range  invalid                              0            st_FOCA0002
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XMLCh         n/a
     *          range  invalid                            XMLCh         n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j)? true : false;

        CANREP_TEST(data_rawstr_1,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_1,    DONT_CARE);
        CANREP_TEST(data_rawstr_2,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_2,    XSValue::st_FOCA0002);

        CANREP_TEST(lex_v_ran_v_1,  dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran_v_1_canrep,  DONT_CARE);
        CANREP_TEST(lex_v_ran_v_2,  dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran_v_2_canrep,  DONT_CARE);

        CANREP_TEST(lex_iv_1        , dt, toValidate, EXP_RET_CANREP_FALSE, 0,                XSValue::st_FOCA0002);
        CANREP_TEST(lex_iv_2        , dt, toValidate, EXP_RET_CANREP_FALSE, 0,                XSValue::st_FOCA0002);

    }

    //validation on
    CANREP_TEST(lex_v_ran_iv_1, dt, true,  EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);
    CANREP_TEST(lex_v_ran_iv_2, dt, true,  EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);

    //validation off
    CANREP_TEST(lex_v_ran_iv_1, dt, false, EXP_RET_CANREP_TRUE,  lex_v_ran_iv_1_canrep, DONT_CARE);
    CANREP_TEST(lex_v_ran_iv_2, dt, false, EXP_RET_CANREP_TRUE,  lex_v_ran_iv_2_canrep, DONT_CARE);
}

//65535
void test_dt_unsignedShort()
{
    const XSValue::DataType dt = XSValue::dt_unsignedShort; 
    bool  toValidate = true;

    const char lex_v_ran_v_0[]="1234";

    const char lex_v_ran_v_1[]="+65535";
    const char lex_v_ran_v_2[]="0";
    const char lex_v_ran_iv_1[]="+65536";
    const char lex_v_ran_iv_2[]="-1";

    const char lex_v_ran_v_1_canrep[]="65535";
    const char lex_v_ran_v_2_canrep[]="0";
    const char lex_v_ran_iv_1_canrep[]="65536";
    const char lex_v_ran_iv_2_canrep[]="-1";

    const char lex_iv_1[]="12b34.456";
    const char lex_iv_2[]="1234b56";

/***
 * 3.3.23.2 Canonical representation
 *
 * The canonical representation for unsignedShort is defined by prohibiting certain options from the 
 * Lexical representation (�3.3.23.1). Specifically, 
 * 1. the leading zeroes are prohibited.
 *
 ***/

    const char data_rawstr_1[]="+12345";
    const char data_canrep_1[]="12345";
    const char data_rawstr_2[]="00012345";
    const char data_canrep_2[]="12345";
   
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *    lexical valid          
     *            range  valid                           true              n/a
     *            range  invalid                         false           st_FOCA0002   
     *    lexical invalid                                false           st_FOCA0002
     * 
     ***/

    // lexical valid, valid range
    VALIDATE_TEST(lex_v_ran_v_0  , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran_v_1  , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran_v_2  , dt, EXP_RET_VALID_TRUE, DONT_CARE);

    // lexical valid, invalid range
    VALIDATE_TEST(lex_v_ran_iv_1 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_v_ran_iv_2 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    // lexical invalid
    VALIDATE_TEST(lex_iv_1         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_iv_2         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        ACTVALUE_TEST(lex_v_ran_v_0,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

        ACTVALUE_TEST(lex_v_ran_v_1,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran_v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran_iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_v_ran_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);

        ACTVALUE_TEST(lex_iv_1,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_iv_2,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XMLCh          n/a
     *          range  invalid                              0            st_FOCA0002
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XMLCh         n/a
     *          range  invalid                            XMLCh         n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j)? true : false;

        CANREP_TEST(data_rawstr_1,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_1,    DONT_CARE);
        CANREP_TEST(data_rawstr_2,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_2,    XSValue::st_FOCA0002);

        CANREP_TEST(lex_v_ran_v_1,  dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran_v_1_canrep,  DONT_CARE);
        CANREP_TEST(lex_v_ran_v_2,  dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran_v_2_canrep,  DONT_CARE);

        CANREP_TEST(lex_iv_1        , dt, toValidate, EXP_RET_CANREP_FALSE, 0,                XSValue::st_FOCA0002);
        CANREP_TEST(lex_iv_2        , dt, toValidate, EXP_RET_CANREP_FALSE, 0,                XSValue::st_FOCA0002);

    }

    //validation on
    CANREP_TEST(lex_v_ran_iv_1, dt, true,  EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);
    CANREP_TEST(lex_v_ran_iv_2, dt, true,  EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);

    //validation off
    CANREP_TEST(lex_v_ran_iv_1, dt, false, EXP_RET_CANREP_TRUE,  lex_v_ran_iv_1_canrep, DONT_CARE);
    CANREP_TEST(lex_v_ran_iv_2, dt, false, EXP_RET_CANREP_TRUE,  lex_v_ran_iv_2_canrep, DONT_CARE);
}

// 255
void test_dt_unsignedByte()
{
    const XSValue::DataType dt = XSValue::dt_unsignedByte; 
    bool  toValidate = true;

    const char lex_v_ran_v_0[]="123";

    const char lex_v_ran_v_1[]="+255";
    const char lex_v_ran_v_2[]="0";
    const char lex_v_ran_iv_1[]="+256";
    const char lex_v_ran_iv_2[]="-1";

    const char lex_v_ran_v_1_canrep[]="255";
    const char lex_v_ran_v_2_canrep[]="0";
    const char lex_v_ran_iv_1_canrep[]="256";
    const char lex_v_ran_iv_2_canrep[]="-1";

    const char lex_iv_1[]="12b34.456";
    const char lex_iv_2[]="1234b56";

/***
 * 3.3.24.2 Canonical representation
 *
 * The canonical representation for unsignedByte is defined by prohibiting certain options from the 
 * Lexical representation (�3.3.24.1). Specifically, 
 * 1. leading zeroes are prohibited.
 *
 ***/

    const char data_rawstr_1[]="+123";
    const char data_canrep_1[]="123";
    const char data_rawstr_2[]="000123";
    const char data_canrep_2[]="123";
   
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *    lexical valid          
     *            range  valid                           true              n/a
     *            range  invalid                         false           st_FOCA0002   
     *    lexical invalid                                false           st_FOCA0002
     * 
     ***/

    // lexical valid, valid range
    VALIDATE_TEST(lex_v_ran_v_0  , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran_v_1  , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran_v_2  , dt, EXP_RET_VALID_TRUE, DONT_CARE);

    // lexical valid, invalid range
    VALIDATE_TEST(lex_v_ran_iv_1 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_v_ran_iv_2 , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    // lexical invalid
    VALIDATE_TEST(lex_iv_1         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_iv_2         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        ACTVALUE_TEST(lex_v_ran_v_0,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

        ACTVALUE_TEST(lex_v_ran_v_1,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran_v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran_iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_v_ran_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);

        ACTVALUE_TEST(lex_iv_1,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_iv_2,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XMLCh          n/a
     *          range  invalid                              0            st_FOCA0002
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XMLCh         n/a
     *          range  invalid                            XMLCh         n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j)? true : false;

        CANREP_TEST(data_rawstr_1,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_1,    DONT_CARE);
        CANREP_TEST(data_rawstr_2,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_2,    XSValue::st_FOCA0002);

        CANREP_TEST(lex_v_ran_v_1,  dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran_v_1_canrep,  DONT_CARE);
        CANREP_TEST(lex_v_ran_v_2,  dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran_v_2_canrep,  DONT_CARE);

        CANREP_TEST(lex_iv_1        , dt, toValidate, EXP_RET_CANREP_FALSE, 0,                XSValue::st_FOCA0002);
        CANREP_TEST(lex_iv_2        , dt, toValidate, EXP_RET_CANREP_FALSE, 0,                XSValue::st_FOCA0002);

    }

    //validation on
    CANREP_TEST(lex_v_ran_iv_1, dt, true,  EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);
    CANREP_TEST(lex_v_ran_iv_2, dt, true,  EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);

    //validation off
    CANREP_TEST(lex_v_ran_iv_1, dt, false, EXP_RET_CANREP_TRUE,  lex_v_ran_iv_1_canrep, DONT_CARE);
    CANREP_TEST(lex_v_ran_iv_2, dt, false, EXP_RET_CANREP_TRUE,  lex_v_ran_iv_2_canrep, DONT_CARE);
}

void test_dt_positiveInteger()
{
    const XSValue::DataType dt = XSValue::dt_positiveInteger; 
    bool  toValidate = true;

    const char lex_v_ran_v_1[]="1234";
    const char lex_v_ran_iv_1[]="0";

    const char lex_v_ran64_v_2[]="+9223372036854775807";
    const char lex_v_ran64_iv_2[]="+9223372036854775808";

    const char lex_v_ran32_v_2[]="2147483647";
    const char lex_v_ran32_iv_2[]="2147483648";

    const char lex_v_ran64_v_2_canrep[]="9223372036854775807";
    const char lex_v_ran64_iv_2_canrep[]="9223372036854775808";

    const char lex_iv_1[]="12b34.456";
    const char lex_iv_2[]="1234b56";

/***
 * 3.3.25.2 Canonical representation 
 *
 * The canonical representation for positiveInteger is defined by prohibiting certain options from the 
 * Lexical representation (�3.3.25.1). Specifically, 
 * 1. the optional "+" sign is prohibited and 
 * 2. leading zeroes are prohibited.
 *
 ***/

    const char data_rawstr_1[]="+1";
    const char data_canrep_1[]="1";
    const char data_rawstr_2[]="+00012345";
    const char data_canrep_2[]="12345";
   
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *    lexical valid          
     *            range  valid                           true              n/a
     *            range  invalid       n/a   
     *    lexical invalid                                false           st_FOCA0002
     * 
     ***/

    // lexical valid
    VALIDATE_TEST(lex_v_ran_v_1    , dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(lex_v_ran_iv_1   , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    VALIDATE_TEST(lex_v_ran64_v_2  , dt, EXP_RET_VALID_TRUE, DONT_CARE);
    VALIDATE_TEST(lex_v_ran64_iv_2 , dt, EXP_RET_VALID_TRUE, DONT_CARE);

    // lexical invalid
    VALIDATE_TEST(lex_iv_1         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_iv_2         , dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XSValue         n/a
     *          range  invalid                              0            st_Unpresentable                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        ACTVALUE_TEST(lex_v_ran_v_1,    dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

#if defined(XML_BITSTOBUILD_64)
        ACTVALUE_TEST(lex_v_ran64_v_2 , dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran64_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0003);
#else
        ACTVALUE_TEST(lex_v_ran32_v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_ran32_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0003);
#endif

        ACTVALUE_TEST(lex_iv_1,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_iv_2,         dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid          
     *          range  valid                              XMLCh          n/a
     *          range  invalid          n/a                  
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid          
     *          range  valid                              XMLCh         n/a
     *          range  invalid          n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j)? true : false;

        CANREP_TEST(data_rawstr_1,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_1,    DONT_CARE);
        CANREP_TEST(data_rawstr_2,    dt, toValidate, EXP_RET_CANREP_TRUE,  data_canrep_2,    DONT_CARE);

        CANREP_TEST(lex_v_ran64_v_2,  dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran64_v_2_canrep,  DONT_CARE);
        CANREP_TEST(lex_v_ran64_iv_2, dt, toValidate, EXP_RET_CANREP_TRUE,  lex_v_ran64_iv_2_canrep, DONT_CARE);
        CANREP_TEST(lex_iv_1        , dt, toValidate, EXP_RET_CANREP_FALSE, 0,                XSValue::st_FOCA0002);
        CANREP_TEST(lex_iv_2        , dt, toValidate, EXP_RET_CANREP_FALSE, 0,                XSValue::st_FOCA0002);

    }

}

void test_dt_boolean()
{
    const XSValue::DataType dt = XSValue::dt_boolean; 
    bool  toValidate = true;

    const char lex_v_1[]="1";
    const char lex_v_2[]="0";
    const char lex_v_3[]="true";
    const char lex_v_4[]="false";

    const char lex_iv_1[]="2";

    const char lex_v_1_canrep[]="true";
    const char lex_v_2_canrep[]="false";
    const char lex_v_3_canrep[]="true";
    const char lex_v_4_canrep[]="false";

/***
 * 3.2.2.2 Canonical representation
 *
 * The canonical representation for boolean is the set of literals {true, false}.
 *
 ***/
  
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *    lexical valid                                  true              n/a
     *    lexical invalid                                false           st_FOCA0002
     * 
     ***/

    // lexical valid
    VALIDATE_TEST(lex_v_1,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(lex_v_2,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(lex_v_3,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(lex_v_4,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    // lexical invalid
    VALIDATE_TEST(lex_iv_1, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid                                    XSValue         n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid                                    XSValue         n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        // lexical valid
        ACTVALUE_TEST(lex_v_1,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_3,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_4,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

        // lexical invalid
        ACTVALUE_TEST(lex_iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *
     *  validation on
     *  ============= 
     *  lexical valid                                    XMLCh            n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid                                    XMLCh            n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        // lexical valid
        CANREP_TEST(lex_v_1,  dt, toValidate, EXP_RET_CANREP_TRUE, lex_v_1_canrep, DONT_CARE);
        CANREP_TEST(lex_v_2,  dt, toValidate, EXP_RET_CANREP_TRUE, lex_v_2_canrep, DONT_CARE);
        CANREP_TEST(lex_v_3,  dt, toValidate, EXP_RET_CANREP_TRUE, lex_v_3_canrep, DONT_CARE);
        CANREP_TEST(lex_v_4,  dt, toValidate, EXP_RET_CANREP_TRUE, lex_v_4_canrep, DONT_CARE);

        // lexical invalid
        CANREP_TEST(lex_iv_1, dt, toValidate, EXP_RET_CANREP_FALSE, 0,             XSValue::st_FOCA0002);
    }

}

void test_dt_hexBinary()
{
    const XSValue::DataType dt = XSValue::dt_hexBinary; 
    bool  toValidate = true;

    const char lex_v_1[]="0fb7";
    const char lex_v_2[]="1234";

    const char lex_iv_1[]="0gb7";
    const char lex_iv_2[]="123";

    const char lex_v_1_canrep[]="0FB7";
    const char lex_v_2_canrep[]="1234";

/***
 * 3.2.15.2 Canonical Rrepresentation
 *
 * The canonical representation for hexBinary is defined by prohibiting certain options from the 
 * Lexical Representation (�3.2.15.1). Specifically, 
 * 1. the lower case hexadecimal digits ([a-f]) are not allowed.
 *
 ***/
  
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *    lexical valid                                  true              n/a
     *    lexical invalid                                false           st_FOCA0002
     * 
     ***/

    // lexical valid
    VALIDATE_TEST(lex_v_1,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(lex_v_2,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    // lexical invalid
    VALIDATE_TEST(lex_iv_1, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_iv_2, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid                                    XSValue         n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid                                    XSValue         n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        // lexical valid
        ACTVALUE_TEST(lex_v_1,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

        // lexical invalid
        ACTVALUE_TEST(lex_iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  
     *  validation on
     *  ============= 
     *  lexical valid                                    XMLCh            n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid                                    XMLCh            n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        // lexical valid
        CANREP_TEST(lex_v_1,  dt, toValidate, EXP_RET_CANREP_TRUE, lex_v_1_canrep, DONT_CARE);
        CANREP_TEST(lex_v_2,  dt, toValidate, EXP_RET_CANREP_TRUE, lex_v_2_canrep, DONT_CARE);

        // lexical invalid
        CANREP_TEST(lex_iv_1, dt, toValidate, EXP_RET_CANREP_FALSE, 0,             XSValue::st_FOCA0002);
        CANREP_TEST(lex_iv_2, dt, toValidate, EXP_RET_CANREP_FALSE, 0,             XSValue::st_FOCA0002);
    }

}

void test_dt_base64Binary()
{
    const XSValue::DataType dt = XSValue::dt_base64Binary; 
    bool  toValidate = true;

    const char lex_v_1[]="134x cv56 gui0";
    const char lex_v_2[]="wxtz 8e4k";

    const char lex_iv_2[]="134xcv56gui";
    const char lex_iv_1[]="wxtz8e4";

    const char lex_v_1_canrep[]="134xcv56gui0";
    const char lex_v_2_canrep[]="wxtz8e4k";

 
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *    lexical valid                                  true              n/a
     *    lexical invalid                                false           st_FOCA0002
     * 
     ***/

    // lexical valid
    VALIDATE_TEST(lex_v_1,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(lex_v_2,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    // lexical invalid
    VALIDATE_TEST(lex_iv_1, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(lex_iv_2, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *  lexical valid                                    XSValue         n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid                                    XSValue         n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        // lexical valid
        ACTVALUE_TEST(lex_v_1,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(lex_v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

        // lexical invalid
        ACTVALUE_TEST(lex_iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(lex_iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  
     *  validation on
     *  ============= 
     *  lexical valid                                    XMLCh            n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *  lexical valid                                    XMLCh            n/a
     *  lexical invalid                                     0            st_FOCA0002
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        // lexical valid
        CANREP_TEST(lex_v_1,  dt, toValidate, EXP_RET_CANREP_TRUE, lex_v_1_canrep, DONT_CARE);
        CANREP_TEST(lex_v_2,  dt, toValidate, EXP_RET_CANREP_TRUE, lex_v_2_canrep, DONT_CARE);

        // lexical invalid
        CANREP_TEST(lex_iv_1, dt, toValidate, EXP_RET_CANREP_FALSE, 0,             XSValue::st_FOCA0002);
        CANREP_TEST(lex_iv_2, dt, toValidate, EXP_RET_CANREP_FALSE, 0,             XSValue::st_FOCA0002);
    }

}

void test_dt_duration()
{
    const XSValue::DataType dt = XSValue::dt_duration; 
    bool  toValidate = true;

    const char v_1[]="P1Y1M1DT1H1M1S";
    const char v_2[]="P1Y1M1DT23H59M59S";
    const char v_3[]="P1Y1M1DT23H";

    const char iv_1[]="P-1Y2M3DT10H30M";
    const char iv_2[]="P1Y1M1DT1H1M1X";
    const char iv_3[]="P1Z1M1DT23H";

    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *     valid                                       true              n/a
     *     invalid                                     false             st_FOCA0002
     * 
     ***/

    //  valid
    VALIDATE_TEST(v_1,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_2,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_3,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    //  invalid
    VALIDATE_TEST(iv_1, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(iv_2, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(iv_3, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *   valid                                          XSValue         n/a
     *   invalid                                           0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                          XSValue         n/a
     *   invalid                                           0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        //  valid
        ACTVALUE_TEST(v_1,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(v_3,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

        //  invalid
        ACTVALUE_TEST(iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(iv_3, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *
     *  validation on
     *  ============= 
     *   valid                                          XMLCh            st_NoCanRep
     *   invalid                                          0              st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                          XMLCh            st_NoCanRep
     *   invalid                                          0              st_NoCanRep
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        //  valid
        CANREP_TEST(v_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);

        //  invalid
        CANREP_TEST(iv_1, dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));
        CANREP_TEST(iv_2, dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));
        CANREP_TEST(iv_3, dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));

    }

}

void test_dt_date()
{
    const XSValue::DataType dt = XSValue::dt_date; 
    bool  toValidate = true;

    const char v_1[]="1991-05-31";
    const char v_2[]="9999-06-30";
    const char v_3[]="99991-07-31";

    const char iv_1[]="2000-12-32";
    const char iv_2[]="2001-02-29";
    const char iv_3[]="2001-06-31";

    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *     valid                                       true              n/a
     *     invalid                                     false             st_FOCA0002
     * 
     ***/

    //  valid
    VALIDATE_TEST(v_1,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_2,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_3,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    //  invalid
    VALIDATE_TEST(iv_1, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(iv_2, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(iv_3, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *   valid                                          XSValue         n/a
     *   invalid                                           0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                          XSValue         n/a
     *   invalid                                           0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        //  valid
        ACTVALUE_TEST(v_1,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(v_3,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

        //  invalid
        ACTVALUE_TEST(iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(iv_3, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *
     *  validation on
     *  ============= 
     *   valid                                          XMLCh            st_NoCanRep
     *   invalid                                          0              st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                          XMLCh            st_NoCanRep
     *   invalid                                          0              st_NoCanRep
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        //  valid
        CANREP_TEST(v_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);

        //  invalid
        CANREP_TEST(iv_1, dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));
        CANREP_TEST(iv_2, dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));
        CANREP_TEST(iv_3, dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));

    }

}

void test_dt_gYearMonth()
{
    const XSValue::DataType dt = XSValue::dt_gYearMonth; 
    bool  toValidate = true;

    const char v_1[]="20000-02";
    const char v_2[]="0200-11";
    const char v_3[]="2000-02";

    const char iv_1[]="0000-12";
    const char iv_2[]="+2000-11";
    const char iv_3[]="2000.90-02";

    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *     valid                                       true              n/a
     *     invalid                                     false             st_FOCA0002
     * 
     ***/

    //  valid
    VALIDATE_TEST(v_1,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_2,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_3,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    //  invalid
    VALIDATE_TEST(iv_1, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(iv_2, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(iv_3, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *   valid                                          XSValue         n/a
     *   invalid                                           0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                          XSValue         n/a
     *   invalid                                           0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        //  valid
        ACTVALUE_TEST(v_1,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(v_3,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

        //  invalid
        ACTVALUE_TEST(iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(iv_3, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *
     *  validation on
     *  ============= 
     *   valid                                          XMLCh            st_NoCanRep
     *   invalid                                          0              st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                          XMLCh            st_NoCanRep
     *   invalid                                          0              st_NoCanRep
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        //  valid
        CANREP_TEST(v_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);

        //  invalid
        CANREP_TEST(iv_1, dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));
        CANREP_TEST(iv_2, dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));
        CANREP_TEST(iv_3, dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));

    }

}

void test_dt_gYear()
{
    const XSValue::DataType dt = XSValue::dt_gYear; 
    bool  toValidate = true;

    const char v_1[]="0001";
    const char v_2[]="9999";
    const char v_3[]="-1999";

    const char iv_1[]="0000";
    const char iv_2[]="+2000";
    const char iv_3[]="2000.90";

    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *     valid                                       true              n/a
     *     invalid                                     false             st_FOCA0002
     * 
     ***/

    //  valid
    VALIDATE_TEST(v_1,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_2,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_3,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    //  invalid
    VALIDATE_TEST(iv_1, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(iv_2, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(iv_3, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *   valid                                          XSValue         n/a
     *   invalid                                           0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                          XSValue         n/a
     *   invalid                                           0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        //  valid
        ACTVALUE_TEST(v_1,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(v_3,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

        //  invalid
        ACTVALUE_TEST(iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(iv_3, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *
     *  validation on
     *  ============= 
     *   valid                                          XMLCh            st_NoCanRep
     *   invalid                                          0              st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                          XMLCh            st_NoCanRep
     *   invalid                                          0              st_NoCanRep
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        //  valid
        CANREP_TEST(v_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);

        //  invalid
        CANREP_TEST(iv_1, dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));
        CANREP_TEST(iv_2, dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));
        CANREP_TEST(iv_3, dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));

    }

}

void test_dt_gMonthDay()
{
    const XSValue::DataType dt = XSValue::dt_gMonthDay; 
    bool  toValidate = true;

    const char v_1[]="--01-31";
    const char v_2[]="--03-31";
    const char v_3[]="--04-01";

    const char iv_1[]="--14-31";
    const char iv_2[]="--12-32";
    const char iv_3[]="--02-30";

    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *     valid                                       true              n/a
     *     invalid                                     false             st_FOCA0002
     * 
     ***/

    //  valid
    VALIDATE_TEST(v_1,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_2,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_3,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    //  invalid
    VALIDATE_TEST(iv_1, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(iv_2, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(iv_3, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *   valid                                          XSValue         n/a
     *   invalid                                           0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                          XSValue         n/a
     *   invalid                                           0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        //  valid
        ACTVALUE_TEST(v_1,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(v_3,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

        //  invalid
        ACTVALUE_TEST(iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(iv_3, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *
     *  validation on
     *  ============= 
     *   valid                                          XMLCh            st_NoCanRep
     *   invalid                                          0              st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                          XMLCh            st_NoCanRep
     *   invalid                                          0              st_NoCanRep
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        //  valid
        CANREP_TEST(v_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);

        //  invalid
        CANREP_TEST(iv_1, dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));
        CANREP_TEST(iv_2, dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));
        CANREP_TEST(iv_3, dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));

    }

}

void test_dt_gDay()
{
    const XSValue::DataType dt = XSValue::dt_gDay; 
    bool  toValidate = true;

    const char v_1[]="---31";
    const char v_2[]="---01";
    const char v_3[]="---28";

    const char iv_1[]="---+31";
    const char iv_2[]="---28.00";
    const char iv_3[]="--31";

    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *     valid                                       true              n/a
     *     invalid                                     false             st_FOCA0002
     * 
     ***/

    //  valid
    VALIDATE_TEST(v_1,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_2,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_3,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    //  invalid
    VALIDATE_TEST(iv_1, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(iv_2, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(iv_3, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *   valid                                          XSValue         n/a
     *   invalid                                           0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                          XSValue         n/a
     *   invalid                                           0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        //  valid
        ACTVALUE_TEST(v_1,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(v_3,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

        //  invalid
        ACTVALUE_TEST(iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(iv_3, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *
     *  validation on
     *  ============= 
     *   valid                                          XMLCh            st_NoCanRep
     *   invalid                                          0              st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                          XMLCh            st_NoCanRep
     *   invalid                                          0              st_NoCanRep
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        //  valid
        CANREP_TEST(v_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);

        //  invalid
        CANREP_TEST(iv_1, dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));
        CANREP_TEST(iv_2, dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));
        CANREP_TEST(iv_3, dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));

    }

}

void test_dt_gMonth()
{
    const XSValue::DataType dt = XSValue::dt_gMonth; 
    bool  toValidate = true;

    const char v_1[]="--02";
    const char v_2[]="--10";
    const char v_3[]="--12";

    const char iv_1[]="--+11";
    const char iv_2[]="---02.09";
    const char iv_3[]="--14--";

    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *     valid                                       true              n/a
     *     invalid                                     false             st_FOCA0002
     * 
     ***/

    //  valid
    VALIDATE_TEST(v_1,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_2,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_3,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    //  invalid
    VALIDATE_TEST(iv_1, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(iv_2, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(iv_3, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *   valid                                          XSValue         n/a
     *   invalid                                           0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                          XSValue         n/a
     *   invalid                                           0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        //  valid
        ACTVALUE_TEST(v_1,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(v_3,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

        //  invalid
        ACTVALUE_TEST(iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(iv_3, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *
     *  validation on
     *  ============= 
     *   valid                                          XMLCh            st_NoCanRep
     *   invalid                                          0              st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                          XMLCh            st_NoCanRep
     *   invalid                                          0              st_NoCanRep
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        //  valid
        CANREP_TEST(v_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);

        //  invalid
        CANREP_TEST(iv_1, dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));
        CANREP_TEST(iv_2, dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));
        CANREP_TEST(iv_3, dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));

    }

}

void test_dt_dateTime()
{
    const XSValue::DataType dt = XSValue::dt_dateTime; 
    bool  toValidate = true;

    const char v_1[]="2000-12-31T23:59:59.00389";
    const char v_2[]="2000-10-01T11:10:20+06:00";
    const char v_3[]="2000-10-01T11:10:20-06:00";

    const char iv_1[]="0000-12-31T23:59:59";
    const char iv_2[]="+2000-11-30T23:59:59Z";
    const char iv_3[]="2000-02-28T23:59.1:59Z";
    const char iv_4[]="2000-11-30T01:01:01Z99";
    const char iv_5[]="2000-02-28T01:01:01Z10:61";

    const char v_1_canrep[]="2000-12-31T23:59:59.00389Z";
    const char v_2_canrep[]="2000-10-01T05:10:20Z";
    const char v_3_canrep[]="2000-10-01T17:10:20Z";

 /***
 * E2-41
 *
 *  3.2.7.2 Canonical representation
 * 
 *  Except for trailing fractional zero digits in the seconds representation, 
 *  '24:00:00' time representations, and timezone (for timezoned values), 
 *  the mapping from literals to values is one-to-one. Where there is more 
 *  than one possible representation, the canonical representation is as follows: 
 *  redundant trailing zero digits in fractional-second literals are prohibited. 
 *  An hour representation of '24' is prohibited. Timezoned values are canonically
 *  represented by appending 'Z' to the nontimezoned representation. (All 
 *  timezoned dateTime values are UTC.) 
 *
 *  .'24:00:00' -> '00:00:00'
 *  .milisecond: trailing zeros removed
 *  .'Z'
 *
 ***/

    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *     valid                                       true              n/a
     *     invalid                                     false             st_FOCA0002
     * 
     ***/

    //  valid
    VALIDATE_TEST(v_1,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_2,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_3,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    //  invalid
    VALIDATE_TEST(iv_1, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(iv_2, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(iv_3, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(iv_4, dt, EXP_RET_VALID_FALSE, XSValue::st_FODT0003);
    VALIDATE_TEST(iv_5, dt, EXP_RET_VALID_FALSE, XSValue::st_FODT0003);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *   valid                                          XSValue         n/a
     *   invalid                                           0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                          XSValue         n/a
     *   invalid                                           0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        //  valid
        ACTVALUE_TEST(v_1,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(v_3,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

        //  invalid
        ACTVALUE_TEST(iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(iv_3, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(iv_4, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FODT0003);
        ACTVALUE_TEST(iv_5, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FODT0003);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *
     *  validation on
     *  ============= 
     *   valid                                          XMLCh            n/a
     *   invalid                                          0              st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                          XMLCh            n/a
     *   invalid                                          0              st_FOCA0002
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        //  valid
        CANREP_TEST(v_1,  dt, toValidate, EXP_RET_CANREP_TRUE, v_1_canrep, DONT_CARE);
        CANREP_TEST(v_2,  dt, toValidate, EXP_RET_CANREP_TRUE, v_2_canrep, DONT_CARE);
        CANREP_TEST(v_3,  dt, toValidate, EXP_RET_CANREP_TRUE, v_3_canrep, DONT_CARE);

        //  invalid
        CANREP_TEST(iv_1, dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);
        CANREP_TEST(iv_2, dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);
        CANREP_TEST(iv_3, dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);
        CANREP_TEST(iv_4, dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_FODT0003);
        CANREP_TEST(iv_5, dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_FODT0003);

    }

}

void test_dt_time()
{
    const XSValue::DataType dt = XSValue::dt_time; 
    bool  toValidate = true;

    const char v_1[]="23:59:59.38900";
    const char v_2[]="24:00:00";
    const char v_3[]="23:59:59";

    const char iv_1[]="55:59:59";
    const char iv_2[]="03:99:59";
    const char iv_3[]="23:59.1:59";
    const char iv_4[]="01:01:01Z99";
    const char iv_5[]="01:01:01Z10:61";

    const char v_1_canrep[]="23:59:59.389Z";
    const char v_2_canrep[]="00:00:00Z";
    const char v_3_canrep[]="23:59:59Z";

/***
 * 3.2.8.2 Canonical representation
 *
 * The canonical representation for time is defined by prohibiting certain options 
 * from the Lexical representation (�3.2.8.1). Specifically, 
 * 1. either the time zone must be omitted or, 
 * 2. if present, the time zone must be Coordinated Universal Time (UTC) 
 *    indicated by a "Z". 
 * 3. Additionally, the canonical representation for midnight is 00:00:00.
 *
 ***/


    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *     valid                                       true              n/a
     *     invalid                                     false             st_FOCA0002
     * 
     ***/

    //  valid
    VALIDATE_TEST(v_1,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_2,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_3,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    //  invalid
    VALIDATE_TEST(iv_1, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(iv_2, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(iv_3, dt, EXP_RET_VALID_FALSE, XSValue::st_FOCA0002);
    VALIDATE_TEST(iv_4, dt, EXP_RET_VALID_FALSE, XSValue::st_FODT0003);
    VALIDATE_TEST(iv_5, dt, EXP_RET_VALID_FALSE, XSValue::st_FODT0003);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *   valid                                          XSValue         n/a
     *   invalid                                           0            st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                          XSValue         n/a
     *   invalid                                           0            st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        //  valid
        ACTVALUE_TEST(v_1,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(v_2,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);
        ACTVALUE_TEST(v_3,  dt, toValidate, EXP_RET_VALUE_TRUE,  DONT_CARE);

        //  invalid
        ACTVALUE_TEST(iv_1, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(iv_2, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(iv_3, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FOCA0002);
        ACTVALUE_TEST(iv_4, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FODT0003);
        ACTVALUE_TEST(iv_5, dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_FODT0003);
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *
     *  validation on
     *  ============= 
     *   valid                                          XMLCh            n/a
     *   invalid                                          0              st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                          XMLCh            n/a
     *   invalid                                          0              st_FOCA0002
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        //  valid
        CANREP_TEST(v_1,  dt, toValidate, EXP_RET_CANREP_TRUE, v_1_canrep, DONT_CARE);
        CANREP_TEST(v_2,  dt, toValidate, EXP_RET_CANREP_TRUE, v_2_canrep, DONT_CARE);
        CANREP_TEST(v_3,  dt, toValidate, EXP_RET_CANREP_TRUE, v_3_canrep, DONT_CARE);

        //  invalid
        CANREP_TEST(iv_1, dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);
        CANREP_TEST(iv_2, dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);
        CANREP_TEST(iv_3, dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_FOCA0002);
        CANREP_TEST(iv_4, dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_FODT0003);
        CANREP_TEST(iv_5, dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_FODT0003);
    }

}

void test_dt_string()
{
    const XSValue::DataType dt = XSValue::dt_string; 
    bool  toValidate = true;

    const char v_1[]="mystring";

    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *     valid                                       true              n/a
     *     invalid                     n/a             false             st_FOCA0002
     * 
     ***/

    //  valid
    VALIDATE_TEST(v_1,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    //  invalid

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *   valid                                             0             n/a
     *   invalid                      n/a                  0             st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                             0             n/a
     *   invalid                      n/a                  0             st_FOCA0002
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        //  valid
        ACTVALUE_TEST(v_1,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);

        //  invalid
    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *
     *  validation on
     *  ============= 
     *   valid                                            0              n/a
     *   invalid                       n/a                0              st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                            0              n/a
     *   invalid                       n/a                0              st_FOCA0002
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        //  valid
        CANREP_TEST(v_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);

        //  invalid

    }

}

void test_dt_anyURI()
{
    const XSValue::DataType dt = XSValue::dt_anyURI; 
    bool  toValidate = true;

    const char v_1[]="http://www.schemaTest.org/IBMd3_2_17v01";
    const char v_2[]="gopher://spinaltap.micro.umn.edu/00/Weather/California/Los%20Angeles";
    const char v_3[]="ftp://www.noNamespace.edu";
  	
    const char iv_1[]="+htp://peiyongz@:90";
    const char iv_2[]=">////1.2.3.4.";
    const char iv_3[]="<///www.ibm.9om";

    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *     valid                                       true              n/a
     *     invalid                                     false             st_FOCA0002
     * 
     ***/

    //  valid
    VALIDATE_TEST(v_1,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_2,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_3,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    //  invalid
    VALIDATE_TEST(iv_1, dt, EXP_RET_VALID_FALSE, DONT_CARE);
    VALIDATE_TEST(iv_2, dt, EXP_RET_VALID_FALSE, DONT_CARE);
    VALIDATE_TEST(iv_3, dt, EXP_RET_VALID_FALSE, DONT_CARE);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *   valid                                             0             st_NoActVal
     *   invalid                                           0             st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                             0             st_NoActVal
     *   invalid                                           0             st_NoActVal
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        //  valid
        ACTVALUE_TEST(v_1,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);
        ACTVALUE_TEST(v_2,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);
        ACTVALUE_TEST(v_3,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);

        //  invalid
        ACTVALUE_TEST(iv_1,  dt, toValidate, EXP_RET_VALUE_FALSE, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoActVal));
        ACTVALUE_TEST(iv_2,  dt, toValidate, EXP_RET_VALUE_FALSE,
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoActVal));
        ACTVALUE_TEST(iv_3,  dt, toValidate, EXP_RET_VALUE_FALSE,
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoActVal));

    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *
     *  validation on
     *  ============= 
     *   valid                                            0              st_NoCanRep
     *   invalid                                          0              st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                            0              st_NoCanRep
     *   invalid                                          0              st_NoCanRep
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        //  valid
        CANREP_TEST(v_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);

        //  invalid
        CANREP_TEST(iv_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));
        CANREP_TEST(iv_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));
        CANREP_TEST(iv_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));
    }

}

void test_dt_QName()
{
    const XSValue::DataType dt = XSValue::dt_QName; 
    bool  toValidate = true;

    const char v_1[]="Ant:Eater";
    const char v_2[]="Minimum_Length";
    const char v_3[]="abcde:a2345";
  	
    const char iv_1[]="Three:Two:One";
    const char iv_2[]=":my";
    const char iv_3[]="+name";

    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *     valid                                       true              n/a
     *     invalid                                     false             st_FOCA0002
     * 
     ***/

    //  valid
    VALIDATE_TEST(v_1,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_2,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_3,  dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    //  invalid
    VALIDATE_TEST(iv_1, dt, EXP_RET_VALID_FALSE,  DONT_CARE);
    VALIDATE_TEST(iv_2, dt, EXP_RET_VALID_FALSE,  DONT_CARE);
    VALIDATE_TEST(iv_3, dt, EXP_RET_VALID_FALSE,  DONT_CARE);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *   valid                                             0             st_NoActVal
     *   invalid                                           0             st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                             0             st_NoActVal
     *   invalid                                           0             st_NoActVal
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        //  valid
        ACTVALUE_TEST(v_1,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);
        ACTVALUE_TEST(v_2,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);
        ACTVALUE_TEST(v_3,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);

        //  invalid
        ACTVALUE_TEST(iv_1,  dt, toValidate, EXP_RET_VALUE_FALSE, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoActVal));
        ACTVALUE_TEST(iv_2,  dt, toValidate, EXP_RET_VALUE_FALSE,
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoActVal));
        ACTVALUE_TEST(iv_3,  dt, toValidate, EXP_RET_VALUE_FALSE,
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoActVal));

    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *
     *  validation on
     *  ============= 
     *   valid                                            0              st_NoCanRep
     *   invalid                                          0              st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                            0              st_NoCanRep
     *   invalid                                          0              st_NoCanRep
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        //  valid
        CANREP_TEST(v_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);

        //  invalid
        CANREP_TEST(iv_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));
        CANREP_TEST(iv_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));
        CANREP_TEST(iv_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate? XSValue::st_FOCA0002: XSValue::st_NoCanRep));
    }

}

void test_dt_NOTATION()
{
    const XSValue::DataType dt = XSValue::dt_NOTATION; 
    bool  toValidate = true;

    const char v_1[]="http://www.ibm.com/test:notation1";
    const char iv_1[]="invaliduri:notation2";
  	
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *     valid                                       true              n/a
     *     invalid                      n/a            false             st_FOCA0002
     * 
     ***/

    //  valid
    VALIDATE_TEST(v_1,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    //  invalid
    VALIDATE_TEST(iv_1,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *   valid                                             0             st_NoActVal
     *   invalid                         n/a               0             st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                             0             st_NoActVal
     *   invalid                         n/a               0             st_NoActVal
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        //  valid
        ACTVALUE_TEST(v_1,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);

        //  invalid


    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *
     *  validation on
     *  ============= 
     *   valid                                            0              st_NoCanRep
     *   invalid                            n/a           0              st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                            0              st_NoCanRep
     *   invalid                            n/a           0              st_NoCanRep
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        //  valid
        CANREP_TEST(v_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);

        //  invalid

    }

}

void test_dt_normalizedString()
{
    const XSValue::DataType dt = XSValue::dt_normalizedString; 
    bool  toValidate = true;
	
    const char v_1[]="4+4=8";
    const char v_2[]="a  b";
    const char v_3[]="someChars=*_-";
    
    const char iv_1[]="a\tb";
    const char iv_2[]="a\nb";
    
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *     valid                                       true              n/a
     *     invalid                      n/a            false             st_FOCA0002
     * 
     ***/

    //  valid
    VALIDATE_TEST(v_1,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_2,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_3,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    //  invalid
    VALIDATE_TEST(iv_1,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);
    VALIDATE_TEST(iv_2,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *   valid                                             0             st_NoActVal
     *   invalid                                           0             st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                             0             st_NoActVal
     *   invalid                                           0             st_NoActVal
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        //  valid
        ACTVALUE_TEST(v_1,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);
        ACTVALUE_TEST(v_2,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);
        ACTVALUE_TEST(v_3,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);

        //  invalid
        ACTVALUE_TEST(iv_1,  dt, toValidate, EXP_RET_VALUE_FALSE, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));
        ACTVALUE_TEST(iv_2,  dt, toValidate, EXP_RET_VALUE_FALSE,
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));

    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *
     *  validation on
     *  ============= 
     *   valid                                            0              st_NoCanRep
     *   invalid                                          0              st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                            0              st_NoCanRep
     *   invalid                                          0              st_NoCanRep
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        //  valid
        CANREP_TEST(v_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);

        //  invalid
        CANREP_TEST(iv_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));
        CANREP_TEST(iv_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));

    }

}

void test_dt_token()
{
    const XSValue::DataType dt = XSValue::dt_token; 
    bool  toValidate = true;
	
    const char v_1[]="4+4=8";
    const char v_2[]="Number2";
    const char v_3[]="someChars=*_-";
    
    const char iv_1[]="a\tb";
    const char iv_2[]="a\nb";
    const char iv_3[]="a  b";
    
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *     valid                                       true              n/a
     *     invalid                      n/a            false             st_FOCA0002
     * 
     ***/

    //  valid
    VALIDATE_TEST(v_1,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_2,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_3,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    //  invalid
    VALIDATE_TEST(iv_1,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);
    VALIDATE_TEST(iv_2,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);
    VALIDATE_TEST(iv_3,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *   valid                                             0             st_NoActVal
     *   invalid                                           0             st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                             0             st_NoActVal
     *   invalid                                           0             st_NoActVal
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        //  valid
        ACTVALUE_TEST(v_1,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);
        ACTVALUE_TEST(v_2,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);
        ACTVALUE_TEST(v_3,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);

        //  invalid
        ACTVALUE_TEST(iv_1,  dt, toValidate, EXP_RET_VALUE_FALSE, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));
        ACTVALUE_TEST(iv_2,  dt, toValidate, EXP_RET_VALUE_FALSE,
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));
        ACTVALUE_TEST(iv_3,  dt, toValidate, EXP_RET_VALUE_FALSE,
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));

    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *
     *  validation on
     *  ============= 
     *   valid                                            0              st_NoCanRep
     *   invalid                                          0              st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                            0              st_NoCanRep
     *   invalid                                          0              st_NoCanRep
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        //  valid
        CANREP_TEST(v_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);

        //  invalid
        CANREP_TEST(iv_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));
        CANREP_TEST(iv_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));
        CANREP_TEST(iv_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));

    }

}

void test_dt_language()
{
    const XSValue::DataType dt = XSValue::dt_language; 
    bool  toValidate = true;
	
    const char v_1[]="en-AT";
    const char v_2[]="ja";
    const char v_3[]="uk-GB";
    
    const char iv_1[]="ja_JP";
    const char iv_2[]="en+US";
    const char iv_3[]="12-en";
    
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *     valid                                       true              n/a
     *     invalid                      n/a            false             st_FOCA0002
     * 
     ***/

    //  valid
    VALIDATE_TEST(v_1,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_2,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_3,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    //  invalid
    VALIDATE_TEST(iv_1,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);
    VALIDATE_TEST(iv_2,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);
    VALIDATE_TEST(iv_3,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *   valid                                             0             st_NoActVal
     *   invalid                                           0             st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                             0             st_NoActVal
     *   invalid                                           0             st_NoActVal
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        //  valid
        ACTVALUE_TEST(v_1,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);
        ACTVALUE_TEST(v_2,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);
        ACTVALUE_TEST(v_3,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);

        //  invalid
        ACTVALUE_TEST(iv_1,  dt, toValidate, EXP_RET_VALUE_FALSE, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));
        ACTVALUE_TEST(iv_2,  dt, toValidate, EXP_RET_VALUE_FALSE,
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));
        ACTVALUE_TEST(iv_3,  dt, toValidate, EXP_RET_VALUE_FALSE,
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));

    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *
     *  validation on
     *  ============= 
     *   valid                                            0              st_NoCanRep
     *   invalid                                          0              st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                            0              st_NoCanRep
     *   invalid                                          0              st_NoCanRep
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        //  valid
        CANREP_TEST(v_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);

        //  invalid
        CANREP_TEST(iv_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));
        CANREP_TEST(iv_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));
        CANREP_TEST(iv_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));

    }

}

void test_dt_NMTOKEN()
{
    const XSValue::DataType dt = XSValue::dt_NMTOKEN; 
    bool  toValidate = true;
  
    const char v_1[]="Four:-_.";
    const char v_2[]="Zeerochert";
    const char v_3[]="007";
    
    const char iv_1[]="#board";
    const char iv_2[]="@com";
    const char iv_3[]=";abc";
    
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *     valid                                       true              n/a
     *     invalid                      n/a            false             st_FOCA0002
     * 
     ***/

    //  valid
    VALIDATE_TEST(v_1,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_2,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_3,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    //  invalid
    VALIDATE_TEST(iv_1,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);
    VALIDATE_TEST(iv_2,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);
    VALIDATE_TEST(iv_3,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *   valid                                             0             st_NoActVal
     *   invalid                                           0             st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                             0             st_NoActVal
     *   invalid                                           0             st_NoActVal
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        //  valid
        ACTVALUE_TEST(v_1,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);
        ACTVALUE_TEST(v_2,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);
        ACTVALUE_TEST(v_3,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);

        //  invalid
        ACTVALUE_TEST(iv_1,  dt, toValidate, EXP_RET_VALUE_FALSE, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));
        ACTVALUE_TEST(iv_2,  dt, toValidate, EXP_RET_VALUE_FALSE,
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));
        ACTVALUE_TEST(iv_3,  dt, toValidate, EXP_RET_VALUE_FALSE,
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));

    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *
     *  validation on
     *  ============= 
     *   valid                                            0              st_NoCanRep
     *   invalid                                          0              st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                            0              st_NoCanRep
     *   invalid                                          0              st_NoCanRep
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        //  valid
        CANREP_TEST(v_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);

        //  invalid
        CANREP_TEST(iv_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));
        CANREP_TEST(iv_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));
        CANREP_TEST(iv_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));

    }

}

void test_dt_NMTOKENS()
{
    const XSValue::DataType dt = XSValue::dt_NMTOKENS; 
    bool  toValidate = true;
  
    const char v_1[]="name1 name2 name3 ";
    const char v_2[]="Zeerochert total number";
    const char v_3[]="007 009 123";
    
    const char iv_1[]="#board";
    const char iv_2[]="@com";
    const char iv_3[]=";abc";
    
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *     valid                                       true              n/a
     *     invalid                      n/a            false             st_FOCA0002
     * 
     ***/

    //  valid
    VALIDATE_TEST(v_1,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_2,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_3,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    //  invalid
    VALIDATE_TEST(iv_1,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);
    VALIDATE_TEST(iv_2,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);
    VALIDATE_TEST(iv_3,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *   valid                                             0             st_NoActVal
     *   invalid                                           0             st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                             0             st_NoActVal
     *   invalid                                           0             st_NoActVal
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        //  valid
        ACTVALUE_TEST(v_1,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);
        ACTVALUE_TEST(v_2,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);
        ACTVALUE_TEST(v_3,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);

        //  invalid
        ACTVALUE_TEST(iv_1,  dt, toValidate, EXP_RET_VALUE_FALSE, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));
        ACTVALUE_TEST(iv_2,  dt, toValidate, EXP_RET_VALUE_FALSE,
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));
        ACTVALUE_TEST(iv_3,  dt, toValidate, EXP_RET_VALUE_FALSE,
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));

    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *
     *  validation on
     *  ============= 
     *   valid                                            0              st_NoCanRep
     *   invalid                                          0              st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                            0              st_NoCanRep
     *   invalid                                          0              st_NoCanRep
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        //  valid
        CANREP_TEST(v_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);

        //  invalid
        CANREP_TEST(iv_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));
        CANREP_TEST(iv_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));
        CANREP_TEST(iv_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));

    }

}

void test_dt_Name()
{
    const XSValue::DataType dt = XSValue::dt_Name; 
    bool  toValidate = true;
  
    const char v_1[]="Four:-_.";
    const char v_2[]="_Zeerochert";
    const char v_3[]=":007";
    
    const char iv_1[]="9name";
    const char iv_2[]="-name";
    const char iv_3[]=".name";
    
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *     valid                                       true              n/a
     *     invalid                      n/a            false             st_FOCA0002
     * 
     ***/

    //  valid
    VALIDATE_TEST(v_1,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_2,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_3,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    //  invalid
    VALIDATE_TEST(iv_1,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);
    VALIDATE_TEST(iv_2,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);
    VALIDATE_TEST(iv_3,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *   valid                                             0             st_NoActVal
     *   invalid                                           0             st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                             0             st_NoActVal
     *   invalid                                           0             st_NoActVal
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        //  valid
        ACTVALUE_TEST(v_1,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);
        ACTVALUE_TEST(v_2,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);
        ACTVALUE_TEST(v_3,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);

        //  invalid
        ACTVALUE_TEST(iv_1,  dt, toValidate, EXP_RET_VALUE_FALSE, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));
        ACTVALUE_TEST(iv_2,  dt, toValidate, EXP_RET_VALUE_FALSE,
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));
        ACTVALUE_TEST(iv_3,  dt, toValidate, EXP_RET_VALUE_FALSE,
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));

    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *
     *  validation on
     *  ============= 
     *   valid                                            0              st_NoCanRep
     *   invalid                                          0              st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                            0              st_NoCanRep
     *   invalid                                          0              st_NoCanRep
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        //  valid
        CANREP_TEST(v_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);

        //  invalid
        CANREP_TEST(iv_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));
        CANREP_TEST(iv_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));
        CANREP_TEST(iv_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));

    }

}

void test_dt_NCName_ID_IDREF_ENTITY(XSValue::DataType dt)
{
    bool  toValidate = true;
  
    const char v_1[]="Four-_.";
    const char v_2[]="_Zeerochert";
    const char v_3[]="L007";
    
    const char iv_1[]=":Four-_.";
    const char iv_2[]="_Zeerochert:";
    const char iv_3[]="0:07";

   
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *     valid                                       true              n/a
     *     invalid                      n/a            false             st_FOCA0002
     * 
     ***/

    //  valid
    VALIDATE_TEST(v_1,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_2,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_3,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    //  invalid
    VALIDATE_TEST(iv_1,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);
    VALIDATE_TEST(iv_2,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);
    VALIDATE_TEST(iv_3,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *   valid                                             0             st_NoActVal
     *   invalid                                           0             st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                             0             st_NoActVal
     *   invalid                                           0             st_NoActVal
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        //  valid
        ACTVALUE_TEST(v_1,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);
        ACTVALUE_TEST(v_2,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);
        ACTVALUE_TEST(v_3,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);

        //  invalid
        ACTVALUE_TEST(iv_1,  dt, toValidate, EXP_RET_VALUE_FALSE, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));
        ACTVALUE_TEST(iv_2,  dt, toValidate, EXP_RET_VALUE_FALSE,
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));
        ACTVALUE_TEST(iv_3,  dt, toValidate, EXP_RET_VALUE_FALSE,
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));

    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *
     *  validation on
     *  ============= 
     *   valid                                            0              st_NoCanRep
     *   invalid                                          0              st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                            0              st_NoCanRep
     *   invalid                                          0              st_NoCanRep
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        //  valid
        CANREP_TEST(v_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);

        //  invalid
        CANREP_TEST(iv_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));
        CANREP_TEST(iv_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));
        CANREP_TEST(iv_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));

    }

}

void test_dt_IDREFS_ENTITIES(XSValue::DataType dt)
{
    bool  toValidate = true;

    const char v_1[]="Four-_. Five Seven";
    const char v_2[]="_Zeerochert _Hundere Bye";
    const char v_3[]="L007 L009 L008";
    
    const char iv_1[]=":Four-_.";
    const char iv_2[]="_Zeerochert:";
    const char iv_3[]="0:07";
     
    /***    
     *
     * validate
     * ---------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *     valid                                       true              n/a
     *     invalid                      n/a            false             st_FOCA0002
     * 
     ***/

    //  valid
    VALIDATE_TEST(v_1,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_2,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);
    VALIDATE_TEST(v_3,   dt, EXP_RET_VALID_TRUE,  DONT_CARE);

    //  invalid
    VALIDATE_TEST(iv_1,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);
    VALIDATE_TEST(iv_2,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);
    VALIDATE_TEST(iv_3,  dt, EXP_RET_VALID_FALSE,  DONT_CARE);

    /***
     *
     * getActualValue
     * ---------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *  validation on
     *  ============= 
     *   valid                                             0             st_NoActVal
     *   invalid                                           0             st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                             0             st_NoActVal
     *   invalid                                           0             st_NoActVal
     *
     ***/
   
    for (int i = 0; i < 2; i++)
    {
        //validation on/off
        toValidate = ( 0 == i) ? true : false;

        //  valid
        ACTVALUE_TEST(v_1,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);
        ACTVALUE_TEST(v_2,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);
        ACTVALUE_TEST(v_3,  dt, toValidate, EXP_RET_VALUE_FALSE, XSValue::st_NoActVal);

        //  invalid
        ACTVALUE_TEST(iv_1,  dt, toValidate, EXP_RET_VALUE_FALSE, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));
        ACTVALUE_TEST(iv_2,  dt, toValidate, EXP_RET_VALUE_FALSE,
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));
        ACTVALUE_TEST(iv_3,  dt, toValidate, EXP_RET_VALUE_FALSE,
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoActVal));

    }

    /***
     *
     * getCanonicalRepresentation
     * ---------------------------
     *                             availability        return value      context
     *                             ----------------------------------------------
     *
     *  validation on
     *  ============= 
     *   valid                                            0              st_NoCanRep
     *   invalid                                          0              st_FOCA0002
     *
     *  validation off
     *  ============== 
     *   valid                                            0              st_NoCanRep
     *   invalid                                          0              st_NoCanRep
     *
     ***/

    for (int j = 0; j < 2; j++)
    {
        //validation on/off
        toValidate = ( 0 == j) ? true : false;

        //  valid
        CANREP_TEST(v_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);
        CANREP_TEST(v_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, XSValue::st_NoCanRep);

        //  invalid
        CANREP_TEST(iv_1,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));
        CANREP_TEST(iv_2,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));
        CANREP_TEST(iv_3,  dt, toValidate, EXP_RET_CANREP_FALSE, 0, 
            (toValidate ? XSValue::st_FOCA0002 : XSValue::st_NoCanRep));

    }

}

void test_DataType()
{

    DATATYPE_TEST( SchemaSymbols::fgDT_STRING,             XSValue::dt_string);
    DATATYPE_TEST( SchemaSymbols::fgDT_BOOLEAN,            XSValue::dt_boolean);
    DATATYPE_TEST( SchemaSymbols::fgDT_DECIMAL,            XSValue::dt_decimal);
    DATATYPE_TEST( SchemaSymbols::fgDT_FLOAT,              XSValue::dt_float);
    DATATYPE_TEST( SchemaSymbols::fgDT_DOUBLE,             XSValue::dt_double);
    DATATYPE_TEST( SchemaSymbols::fgDT_DURATION,           XSValue::dt_duration);
    DATATYPE_TEST( SchemaSymbols::fgDT_DATETIME,           XSValue::dt_dateTime);
    DATATYPE_TEST( SchemaSymbols::fgDT_TIME,               XSValue::dt_time);
    DATATYPE_TEST( SchemaSymbols::fgDT_DATE,               XSValue::dt_date);
    DATATYPE_TEST( SchemaSymbols::fgDT_YEARMONTH,          XSValue::dt_gYearMonth);
    DATATYPE_TEST( SchemaSymbols::fgDT_YEAR,               XSValue::dt_gYear);
    DATATYPE_TEST( SchemaSymbols::fgDT_MONTHDAY,           XSValue::dt_gMonthDay);
    DATATYPE_TEST( SchemaSymbols::fgDT_DAY,                XSValue::dt_gDay);
    DATATYPE_TEST( SchemaSymbols::fgDT_MONTH,              XSValue::dt_gMonth);
    DATATYPE_TEST( SchemaSymbols::fgDT_HEXBINARY,          XSValue::dt_hexBinary);
    DATATYPE_TEST( SchemaSymbols::fgDT_BASE64BINARY,       XSValue::dt_base64Binary);
    DATATYPE_TEST( SchemaSymbols::fgDT_ANYURI,             XSValue::dt_anyURI);
    DATATYPE_TEST( SchemaSymbols::fgDT_QNAME,              XSValue::dt_QName);
    DATATYPE_TEST( XMLUni::fgNotationString,               XSValue::dt_NOTATION);
    DATATYPE_TEST( SchemaSymbols::fgDT_NORMALIZEDSTRING,   XSValue::dt_normalizedString);
    DATATYPE_TEST( SchemaSymbols::fgDT_TOKEN,              XSValue::dt_token);
    DATATYPE_TEST( SchemaSymbols::fgDT_LANGUAGE,           XSValue::dt_language);
    DATATYPE_TEST( XMLUni::fgNmTokenString,                XSValue::dt_NMTOKEN);
    DATATYPE_TEST( XMLUni::fgNmTokensString,               XSValue::dt_NMTOKENS);
    DATATYPE_TEST( SchemaSymbols::fgDT_NAME,               XSValue::dt_Name);
    DATATYPE_TEST( SchemaSymbols::fgDT_NCNAME,             XSValue::dt_NCName);
    DATATYPE_TEST( XMLUni::fgIDString,                     XSValue::dt_ID);
    DATATYPE_TEST( XMLUni::fgIDRefString,                  XSValue::dt_IDREF);
    DATATYPE_TEST( XMLUni::fgIDRefsString,                 XSValue::dt_IDREFS);
    DATATYPE_TEST( XMLUni::fgEntityString,                 XSValue::dt_ENTITY);
    DATATYPE_TEST( XMLUni::fgEntitiesString,               XSValue::dt_ENTITIES);
    DATATYPE_TEST( SchemaSymbols::fgDT_INTEGER,            XSValue::dt_integer);
    DATATYPE_TEST( SchemaSymbols::fgDT_NONPOSITIVEINTEGER, XSValue::dt_nonPositiveInteger);
    DATATYPE_TEST( SchemaSymbols::fgDT_NEGATIVEINTEGER,    XSValue::dt_negativeInteger);
    DATATYPE_TEST( SchemaSymbols::fgDT_LONG,               XSValue::dt_long);
    DATATYPE_TEST( SchemaSymbols::fgDT_INT,                XSValue::dt_int);
    DATATYPE_TEST( SchemaSymbols::fgDT_SHORT,              XSValue::dt_short);
    DATATYPE_TEST( SchemaSymbols::fgDT_BYTE,               XSValue::dt_byte);
    DATATYPE_TEST( SchemaSymbols::fgDT_NONNEGATIVEINTEGER, XSValue::dt_nonNegativeInteger);
    DATATYPE_TEST( SchemaSymbols::fgDT_ULONG,              XSValue::dt_unsignedLong);
    DATATYPE_TEST( SchemaSymbols::fgDT_UINT,               XSValue::dt_unsignedInt);
    DATATYPE_TEST( SchemaSymbols::fgDT_USHORT,             XSValue::dt_unsignedShort);
    DATATYPE_TEST( SchemaSymbols::fgDT_UBYTE,              XSValue::dt_unsignedByte);
    DATATYPE_TEST( SchemaSymbols::fgDT_POSITIVEINTEGER,    XSValue::dt_positiveInteger);

    DATATYPE_TEST( XMLUni::fgLongMaxInc,                   XSValue::dt_MAXCOUNT);
}

void testErrorStatus()
{
/***
DataType	Interface	Inv Char	Out-Of-Bound	To Big for C Type
dt_decimal  canRep      st_FOCA0002  n.a.	        n.a.
	        actVal      st_FOCA0002	n.a.            st_FOCA0001
***/

    {
        const char d1[]="12b34.456";
        const char d2[]="44444444444466666666666666666666666666666666666666666666666666666555555555555555555555555555555555555555555555555444294967296444444444444444444444444444445555555555555555555555555555555555555555555555555555555555555555555555555222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222.999";

        testNoCanRep(d1, XSValue::dt_decimal, XSValue::st_FOCA0002);

        testNoActVal(d1, XSValue::dt_decimal, XSValue::st_FOCA0002);
        testNoActVal(d2, XSValue::dt_decimal, XSValue::st_FOCA0001);
    }

/***    
dt_float    canRep	st_FOCA0002	st_FOCA0002	n.a.
	        actVal	st_FOCA0002	st_FOCA0002	n.a.
***/
    {
        const char d1[]="+3.402823466e+39";
        const char d2[]="-3.4028234x66";
        const char d3[]="+1.175494351e-39";

        testNoCanRep(d1, XSValue::dt_float, XSValue::st_FOCA0002);
        testNoCanRep(d2, XSValue::dt_float, XSValue::st_FOCA0002);
        testNoCanRep(d3, XSValue::dt_float, XSValue::st_FOCA0002);

        testNoActVal(d1, XSValue::dt_float, XSValue::st_FOCA0002);
        testNoActVal(d2, XSValue::dt_float, XSValue::st_FOCA0002);
        testNoActVal(d3, XSValue::dt_float, XSValue::st_FOCA0002);

    }

/***				
dt_double	canRep	st_FOCA0002	st_FOCA0002	n.a.
	        actVal	st_FOCA0002	st_FOCA0002	n.a.
***/
    {
        const char d1[]="+3.402823466e+308";
        const char d2[]="-3.4028234x66";
        const char d3[]="+1.175494351e-329";

        testNoCanRep(d1, XSValue::dt_double, XSValue::st_FOCA0002);
        testNoCanRep(d2, XSValue::dt_double, XSValue::st_FOCA0002);
        testNoCanRep(d3, XSValue::dt_double, XSValue::st_FOCA0002);

        testNoActVal(d1, XSValue::dt_double, XSValue::st_FOCA0002);
        testNoActVal(d2, XSValue::dt_double, XSValue::st_FOCA0002);
        testNoActVal(d3, XSValue::dt_double, XSValue::st_FOCA0002);

    }

/***				
dt_integer 	canRep	st_FOCA0002	n.a.	n.a.
        	actVal	st_FOCA0002	n.a.	st_FOCA0003
***/
    {
        const char d1[]="+2147483648";
        const char d2[]="-2147483649";
        const char d3[]="123x456";
        const char d4[]="123.456";

        testNoCanRep(d3, XSValue::dt_integer, XSValue::st_FOCA0002);
        testNoCanRep(d4, XSValue::dt_integer, XSValue::st_FOCA0002);

        testNoActVal(d1, XSValue::dt_integer, XSValue::st_FOCA0003);
        testNoActVal(d2, XSValue::dt_integer, XSValue::st_FOCA0003);
        testNoActVal(d3, XSValue::dt_integer, XSValue::st_FOCA0002);
        testNoActVal(d4, XSValue::dt_integer, XSValue::st_FOCA0002);
    }

/***				
dt_negativeInteger canRep	st_FOCA0002	st_FOCA0002	n.a.
	               actVal	st_FOCA0002	st_FOCA0002	st_FOCA0003
***/
    {
        const char d1[]="0";
        const char d2[]="-2147483649";
        const char d3[]="123x456";
        const char d4[]="123.456";

        testNoCanRep(d1, XSValue::dt_negativeInteger, XSValue::st_FOCA0002);
        testNoCanRep(d3, XSValue::dt_negativeInteger, XSValue::st_FOCA0002);
        testNoCanRep(d4, XSValue::dt_negativeInteger, XSValue::st_FOCA0002);

        testNoActVal(d1, XSValue::dt_negativeInteger, XSValue::st_FOCA0002);
        testNoActVal(d2, XSValue::dt_negativeInteger, XSValue::st_FOCA0003);
        testNoActVal(d3, XSValue::dt_negativeInteger, XSValue::st_FOCA0002);
        testNoActVal(d4, XSValue::dt_negativeInteger, XSValue::st_FOCA0002);
    }
    
/***    
dt_nonPositiveInteger	canRep	st_FOCA0002	st_FOCA0002	n.a.
	                    actVal	st_FOCA0002	st_FOCA0002	st_FOCA0003
***/	
    {
        const char d1[]="1";
        const char d2[]="-2147483649";
        const char d3[]="123x456";
        const char d4[]="123.456";

        testNoCanRep(d1, XSValue::dt_nonPositiveInteger, XSValue::st_FOCA0002);
        testNoCanRep(d3, XSValue::dt_nonPositiveInteger, XSValue::st_FOCA0002);
        testNoCanRep(d4, XSValue::dt_nonPositiveInteger, XSValue::st_FOCA0002);

        testNoActVal(d1, XSValue::dt_nonPositiveInteger, XSValue::st_FOCA0002);
        testNoActVal(d2, XSValue::dt_nonPositiveInteger, XSValue::st_FOCA0003);
        testNoActVal(d3, XSValue::dt_nonPositiveInteger, XSValue::st_FOCA0002);
        testNoActVal(d4, XSValue::dt_nonPositiveInteger, XSValue::st_FOCA0002);
    }      
/***
dt_nonNegativeInteger   	canRep	st_FOCA0002	st_FOCA0002	n.a.
	                        actVal	st_FOCA0002	st_FOCA0002	st_FOCA0003
***/	
    {
        const char d1[]="-1";
        const char d2[]="+2147483649";
        const char d3[]="123x456";
        const char d4[]="123.456";

        testNoCanRep(d1, XSValue::dt_nonNegativeInteger, XSValue::st_FOCA0002);
        testNoCanRep(d3, XSValue::dt_nonNegativeInteger, XSValue::st_FOCA0002);
        testNoCanRep(d4, XSValue::dt_nonNegativeInteger, XSValue::st_FOCA0002);

        testNoActVal(d1, XSValue::dt_nonNegativeInteger, XSValue::st_FOCA0002);
        testNoActVal(d2, XSValue::dt_nonNegativeInteger, XSValue::st_FOCA0003);
        testNoActVal(d3, XSValue::dt_nonNegativeInteger, XSValue::st_FOCA0002);
        testNoActVal(d4, XSValue::dt_nonNegativeInteger, XSValue::st_FOCA0002);
    }      

/***
dt_positiveInteger    	canRep	st_FOCA0002	st_FOCA0002	n.a.
                     	actVal	st_FOCA0002	st_FOCA0002	st_FOCA0003
***/
    {
        const char d1[]="0";
        const char d2[]="+2147483649";
        const char d3[]="123x456";
        const char d4[]="123.456";

        testNoCanRep(d1, XSValue::dt_positiveInteger, XSValue::st_FOCA0002);
        testNoCanRep(d3, XSValue::dt_positiveInteger, XSValue::st_FOCA0002);
        testNoCanRep(d4, XSValue::dt_positiveInteger, XSValue::st_FOCA0002);

        testNoActVal(d1, XSValue::dt_positiveInteger, XSValue::st_FOCA0002);
        testNoActVal(d2, XSValue::dt_positiveInteger, XSValue::st_FOCA0003);
        testNoActVal(d3, XSValue::dt_positiveInteger, XSValue::st_FOCA0002);
        testNoActVal(d4, XSValue::dt_positiveInteger, XSValue::st_FOCA0002);
    }

/***				
dt_long   canRep	st_FOCA0002	st_FOCA0002	n.a.
	      actVal	st_FOCA0002	st_FOCA0002	st_FOCA0003.
***/
    {
        const char d1[]="-9223372036854775809";
        const char d2[]="+9223372036854775808";
        const char d3[]="123x456";
        const char d4[]="123.456";
        const char d5[]="-92233720368547758";
        const char d6[]="+92233720368547758";

        testNoCanRep(d1, XSValue::dt_long, XSValue::st_FOCA0002);
        testNoCanRep(d2, XSValue::dt_long, XSValue::st_FOCA0002);
        testNoCanRep(d3, XSValue::dt_long, XSValue::st_FOCA0002);
        testNoCanRep(d4, XSValue::dt_long, XSValue::st_FOCA0002);

        testNoActVal(d5, XSValue::dt_long, XSValue::st_FOCA0003);
        testNoActVal(d6, XSValue::dt_long, XSValue::st_FOCA0003);
        testNoActVal(d3, XSValue::dt_long, XSValue::st_FOCA0002);
        testNoActVal(d4, XSValue::dt_long, XSValue::st_FOCA0002);
    }
    
/***    
dt_int	canRep	st_FOCA0002	st_FOCA0002	n.a.
	    actVal	st_FOCA0002	st_FOCA0002	n.a.
***/
    {
        const char d1[]="-2147483649";
        const char d2[]="+2147483648";
        const char d3[]="123x456";
        const char d4[]="123.456";

        testNoCanRep(d1, XSValue::dt_int, XSValue::st_FOCA0002);
        testNoCanRep(d2, XSValue::dt_int, XSValue::st_FOCA0002);
        testNoCanRep(d3, XSValue::dt_int, XSValue::st_FOCA0002);
        testNoCanRep(d4, XSValue::dt_int, XSValue::st_FOCA0002);

        testNoActVal(d1, XSValue::dt_int, XSValue::st_FOCA0002);
        testNoActVal(d2, XSValue::dt_int, XSValue::st_FOCA0002);
        testNoActVal(d3, XSValue::dt_int, XSValue::st_FOCA0002);
        testNoActVal(d4, XSValue::dt_int, XSValue::st_FOCA0002);
    }

/***				
dt_short	canRep	st_FOCA0002	st_FOCA0002	n.a.
	        actVal	st_FOCA0002	st_FOCA0002	n.a.
***/
    {
        const char d1[]="-32769";
        const char d2[]="+32768";
        const char d3[]="123x456";
        const char d4[]="123.456";

        testNoCanRep(d1, XSValue::dt_short, XSValue::st_FOCA0002);
        testNoCanRep(d2, XSValue::dt_short, XSValue::st_FOCA0002);
        testNoCanRep(d3, XSValue::dt_short, XSValue::st_FOCA0002);
        testNoCanRep(d4, XSValue::dt_short, XSValue::st_FOCA0002);

        testNoActVal(d1, XSValue::dt_short, XSValue::st_FOCA0002);
        testNoActVal(d2, XSValue::dt_short, XSValue::st_FOCA0002);
        testNoActVal(d3, XSValue::dt_short, XSValue::st_FOCA0002);
        testNoActVal(d4, XSValue::dt_short, XSValue::st_FOCA0002);
    }
    
/***    
dt_byte	canRep	st_FOCA0002	st_FOCA0002	n.a.
	    actVal	st_FOCA0002	st_FOCA0002	n.a.
***/
    {
        const char d1[]="-129";
        const char d2[]="+128";
        const char d3[]="123x456";
        const char d4[]="123.456";

        testNoCanRep(d1, XSValue::dt_byte, XSValue::st_FOCA0002);
        testNoCanRep(d2, XSValue::dt_byte, XSValue::st_FOCA0002);
        testNoCanRep(d3, XSValue::dt_byte, XSValue::st_FOCA0002);
        testNoCanRep(d4, XSValue::dt_byte, XSValue::st_FOCA0002);

        testNoActVal(d1, XSValue::dt_byte, XSValue::st_FOCA0002);
        testNoActVal(d2, XSValue::dt_byte, XSValue::st_FOCA0002);
        testNoActVal(d3, XSValue::dt_byte, XSValue::st_FOCA0002);
        testNoActVal(d4, XSValue::dt_byte, XSValue::st_FOCA0002);
    }

/***				
dt_unsignedLong	canRep	st_FOCA0002	st_FOCA0002	n.a.
	actVal	st_FOCA0002	st_FOCA0002	n.a.
***/
    {
        const char d1[]="-1";
        const char d2[]="+18446744073709551616";
        const char d3[]="123x456";
        const char d4[]="123.456";
        const char d5[]="-3";
        const char d6[]="+92233720368547758";

        testNoCanRep(d1, XSValue::dt_unsignedLong, XSValue::st_FOCA0002);
        testNoCanRep(d2, XSValue::dt_unsignedLong, XSValue::st_FOCA0002);
        testNoCanRep(d3, XSValue::dt_unsignedLong, XSValue::st_FOCA0002);
        testNoCanRep(d4, XSValue::dt_unsignedLong, XSValue::st_FOCA0002);

        testNoActVal(d5, XSValue::dt_unsignedLong, XSValue::st_FOCA0002);
        testNoActVal(d6, XSValue::dt_unsignedLong, XSValue::st_FOCA0003);
        testNoActVal(d3, XSValue::dt_unsignedLong, XSValue::st_FOCA0002);
        testNoActVal(d4, XSValue::dt_unsignedLong, XSValue::st_FOCA0002);
    }

/***    
dt_unsignedInt	canRep	st_FOCA0002	st_FOCA0002	n.a.
	            actVal	st_FOCA0002	st_FOCA0002	n.a.
***/
    {
        const char d1[]="-1";
        const char d2[]="+4294967296";
        const char d3[]="123x456";
        const char d4[]="123.456";

        testNoCanRep(d1, XSValue::dt_unsignedInt, XSValue::st_FOCA0002);
        testNoCanRep(d2, XSValue::dt_unsignedInt, XSValue::st_FOCA0002);
        testNoCanRep(d3, XSValue::dt_unsignedInt, XSValue::st_FOCA0002);
        testNoCanRep(d4, XSValue::dt_unsignedInt, XSValue::st_FOCA0002);

        testNoActVal(d1, XSValue::dt_unsignedInt, XSValue::st_FOCA0002);
        testNoActVal(d2, XSValue::dt_unsignedInt, XSValue::st_FOCA0002);
        testNoActVal(d3, XSValue::dt_unsignedInt, XSValue::st_FOCA0002);
        testNoActVal(d4, XSValue::dt_unsignedInt, XSValue::st_FOCA0002);
    }
    
/***    
dt_unsignedShort	canRep	st_FOCA0002	st_FOCA0002	n.a.
                	actVal	st_FOCA0002	st_FOCA0002	n.a.
***/
    {
        const char d1[]="-1";
        const char d2[]="+65536";
        const char d3[]="123x456";
        const char d4[]="123.456";

        testNoCanRep(d1, XSValue::dt_unsignedShort, XSValue::st_FOCA0002);
        testNoCanRep(d2, XSValue::dt_unsignedShort, XSValue::st_FOCA0002);
        testNoCanRep(d3, XSValue::dt_unsignedShort, XSValue::st_FOCA0002);
        testNoCanRep(d4, XSValue::dt_unsignedShort, XSValue::st_FOCA0002);

        testNoActVal(d1, XSValue::dt_unsignedShort, XSValue::st_FOCA0002);
        testNoActVal(d2, XSValue::dt_unsignedShort, XSValue::st_FOCA0002);
        testNoActVal(d3, XSValue::dt_unsignedShort, XSValue::st_FOCA0002);
        testNoActVal(d4, XSValue::dt_unsignedShort, XSValue::st_FOCA0002);
    }	
/***    
dt_unsignedByte	canRep	st_FOCA0002	st_FOCA0002	n.a.
	actVal	st_FOCA0002	st_FOCA0002	n.a.
***/
    {
        const char d1[]="-1";
        const char d2[]="+256";
        const char d3[]="123x456";
        const char d4[]="123.456";

        testNoCanRep(d1, XSValue::dt_unsignedByte, XSValue::st_FOCA0002);
        testNoCanRep(d2, XSValue::dt_unsignedByte, XSValue::st_FOCA0002);
        testNoCanRep(d3, XSValue::dt_unsignedByte, XSValue::st_FOCA0002);
        testNoCanRep(d4, XSValue::dt_unsignedByte, XSValue::st_FOCA0002);

        testNoActVal(d1, XSValue::dt_unsignedByte, XSValue::st_FOCA0002);
        testNoActVal(d2, XSValue::dt_unsignedByte, XSValue::st_FOCA0002);
        testNoActVal(d3, XSValue::dt_unsignedByte, XSValue::st_FOCA0002);
        testNoActVal(d4, XSValue::dt_unsignedByte, XSValue::st_FOCA0002);
    }

}

// ---------------------------------------------------------------------------
//  Program entry point
// ---------------------------------------------------------------------------
int main(int, char* )
{

    // Initialize the XML4C system
    try
    {
        XMLPlatformUtils::Initialize();
    }

    catch (const XMLException& toCatch)
    {
        XERCES_STD_QUALIFIER cerr << "Error during initialization! Message:\n"
            << StrX(toCatch.getMessage()) << XERCES_STD_QUALIFIER endl;
        return 1;
    }

    test_dt_string();              
    test_dt_boolean();
    test_dt_decimal();
    test_dt_float();
    test_dt_double();
    test_dt_duration();
    test_dt_dateTime();
    test_dt_time();
    test_dt_date();
    test_dt_gYearMonth();
    test_dt_gYear();
    test_dt_gMonthDay();
    test_dt_gDay();
    test_dt_gMonth();
    test_dt_hexBinary();
    test_dt_base64Binary();
    test_dt_anyURI();
    test_dt_QName();
    test_dt_NOTATION();
    test_dt_normalizedString();
    test_dt_token();
    test_dt_language();
    test_dt_NMTOKEN();
    test_dt_NMTOKENS();
    test_dt_Name();    
    test_dt_NCName_ID_IDREF_ENTITY(XSValue::dt_NCName);
    test_dt_NCName_ID_IDREF_ENTITY(XSValue::dt_ID);
    test_dt_NCName_ID_IDREF_ENTITY(XSValue::dt_IDREF);
    test_dt_IDREFS_ENTITIES(XSValue::dt_IDREFS);
    test_dt_NCName_ID_IDREF_ENTITY(XSValue::dt_ENTITY);
    test_dt_IDREFS_ENTITIES(XSValue::dt_ENTITIES);   
    test_dt_integer();
    test_dt_nonPositiveInteger();
    test_dt_negativeInteger();
    test_dt_long();
    test_dt_int();
    test_dt_short();
    test_dt_byte();
    test_dt_nonNegativeInteger();
    test_dt_unsignedLong();
    test_dt_unsignedInt();
    test_dt_unsignedShort();
    test_dt_unsignedByte();
    test_dt_positiveInteger();

    test_DataType();

    printf("\nXSValueTest %s\n", errSeen? "Fail" : "Pass");

    // And call the termination method
    XMLPlatformUtils::Terminate();

    return 0;
}
