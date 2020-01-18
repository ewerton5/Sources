/*
Universidade Federal do Rio de Janeiro
Escola Politecnica
Departamento de Eletronica e de Computacao
Prof. Marcelo Luiz Drumond Lanza
EEL 270 - Computacao II - Turma 2019/2
 
$Author: ewerton.silles $
$Date: 2019/12/24 13:52:26 $
$Log: dvfmEvsUml.c,v $
Revision 1.1  2019/12/24 13:52:26  ewerton.silles
Initial revision

*/

#ifdef __FreeBSD__
#include                            <pwd.h>
#endif

#include                            <stdlib.h>
#include                            <getopt.h>
#include                            <string.h>
#include                            <stdio.h>
#include                            <unistd.h>
#include                            <sys/types.h>
#include                           "dvfmEvsUmlTypes.h"
#include                           "dvfmEvsUmlErrors.h"
#include                           "dvfmEvsUmlConfig.h"
#include                           "dvfmEvsUmlUserInterface.h"
#include                           "dvfmEvsUmlConst.h"
#include                           "dvfmEvsUmlFunctions.h"
#include	                       "dvfmEvsUmlShowCliHelp.h"
#include                           "dvfmEvsUmlAddUser.h"

#ifdef __linux__
#define _XOPEN_SOURCE 600
#endif

#define DVFM_EVS_UML_MINIMUM_NUMBER_ARGUMENTS       2
#define DVFM_EVS_UML_MAXIMUM_NUMBER_ARGUMENTS       10
#define DVFM_EVS_UML_QUANTITY_OPTIONS               24
#define DVFM_EVS_UML_START_SUB_OPTIONS              2
#define DVFM_EVS_UML_EOS                            '\0'


#define DVFM_EVS_UML_REQUIRED_SUBOPTION_SHOW_CLI_HELP_H                                 0
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_SHOW_CONFIGURATION_VALUES_O                     0
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_RUN_NCURSES_INTERFACE_N                         0
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_ADD_USER_C                                      4
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_ADD_USER_A                                      6
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_ADD_USER_I                                      6
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_ACCEPT_INVITE_T                                 1
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_REJECT_INVITE_J                                 1
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_REQUEST_REGISTRATION_N                          5
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_GET_PENDING_REGISTRATION_REQUESTS_PER_USER_Q    1
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_GET_PENDING_REGISTRATION_REQUESTS_Q             1
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_APPROVED_REGISTRATION_REQUEST_V                 2
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_DISAPPROVE_REGISTRATION_REQUEST_D               2
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_GET_UNLOCKING_REQUESTS_U                        1
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_LOCK_USER_ACCOUNT_L                             1
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_UNLOCK_USER_ACCOUNT_U                           1
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_CHANGE_USER_PASSWORD_P                          1
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_RESET_USER_PASSWORD_R                           1
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_CHANGE_USER_NAME_M                              3
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_CHANGE_USER_EMAIL_E                             3
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_CONFIRM_EMAIL_CHANGE_C                          2
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_CHANGE_USER_PROFILE_G                           3
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_GET_USERS_S                                     0
#define DVFM_EVS_UML_REQUIRED_SUBOPTION_SEARCH_USERS_S                                  0

#define DVFM_EVS_UML_OK                                                 0
#define DVFM_EVS_UML_INVALID_NUMBER_ARGUMENTS_SHORT                     1
#define DVFM_EVS_UML_INVALID_NUMBER_ARGUMENTS_LONG                      2
#define DVFM_EVS_UML_INVALID_POSITION_OPTION                            3
#define DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT                   4
#define DVFM_EVS_UML_INVALID_SUB_OPTIONS                                5
#define DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION                          6
#define DVFM_EVS_UML_INVALID_OPTIONS                                    7
#define DVFM_EVS_UML_CONVERT_ADMINISTRATOR_ID                           8
#define DVFM_EVS_UML_INVALID_ID                                         9
#define DVFM_EVS_UML_ERROR_FUNCTION_CONFIGURATION_OPTIONS               10
#define DVFM_EVS_UML_ERROR_FUNCTION_ADD_USER                            11

int
main (int argc, char *argv[])
{
    char *dvfmEvsUmlShortOption = "hoNCaitjnqQvdUluprmecgsS";

    opterr = 0;

    struct option dvfmEvsUmlLongOption [DVFM_EVS_UML_QUANTITY_OPTIONS + 1]=
	{
		{"help", 2, NULL, 'h'},
		{"options", 2, NULL, 'o'},
        {"Ncurses", 2, NULL, 'N'},
        {"Configure", 2, NULL, 'C'},
        {"add", 2, NULL, 'a'},
        {"invite", 2, NULL, 'i'},
        {"accept", 2, NULL, 't'},
        {"reject", 2, NULL, 'j'},
        {"new", 2, NULL, 'n'},
        {"request", 2, NULL, 'q'},
        {"Request", 2, NULL, 'Q'},
        {"approve", 2, NULL, 'v'},
        {"disapprove", 2, NULL, 'd'},
        {"Unlocking", 2, NULL, 'U'},
        {"lock", 2, NULL, 'l'},
        {"unlock", 2, NULL, 'u'},
        {"password", 2, NULL, 'p'},
        {"reset", 2, NULL, 'r'},
        {"modify", 2, NULL, 'm'},
        {"edit", 2, NULL, 'e'},
        {"confirm", 2, NULL, 'c'},
        {"group", 2, NULL, 'g'},
        {"show", 2, NULL, 's'},
        {"Search", 2, NULL, 'S'},
        {NULL, 0, NULL, 0}
	};

    int dvfmEvsUmlCurrentOption;

    enum
    {
        dvfmEvsUmlIndexConfiguration,
        dvfmEvsUmlIndexLanguage,
        dvfmEvsUmlIndexUser,
        dvfmEvsUmlIndexUsername,
        dvfmEvsUmlIndexConfirmUsername,
        dvfmEvsUmlIndexEmail,
        dvfmEvsUmlIndexConfirmEmail,
        dvfmEvsUmlIndexProfile,
        dvfmEvsUmlIndexFriendEmail,
        dvfmEvsUmlIndexNickname,
        dvfmEvsUmlIndexKey,
        dvfmEvsUmlSizeSubOption
    };

    char *dvfmEvsUmlConfiguration = "";
    dvfmEvsUmlLanguageType dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;
    char *dvfmEvsUmlUser = "";
    char *dvfmEvsUmlNickname = "";
    char *dvfmEvsUmlConfirmNickname = "";
    char *dvfmEvsUmlEmail = "";
    char *dvfmEvsUmlConfirmEmail = "";
    char *dvfmEvsUmlProfile = "";
    char *dvfmEvsUmlFriendEmail = "";
    char *dvfmEvsUmlNickname = "";
    char *dvfmEvsUmlKey = "";
   

    char *dvfmEvsUmlSubOption [dvfmEvsUmlSizeSubOption + 1] = 
    {
        "configuration",
        "language",
        "user",
        "username",
        "confirm-username",
        "email",
        "confirm-email",
        "profile",
        "friend-email",
        "nickname",
        "key",
        NULL
    };

    int dvfmEvsUmlIndexArgument, dvfmEvsUmlIndexNameSubOption;
    char *dvfmEvsUmlCurrentArgument;
    char *dvfmEvsUmlValueSubOption;

    int dvfmEvsUmlMandatorySubOptionOccurs = 0;

    char *dvfmEvsUmlValidation;
    unsigned long dvfmEvsUmlIdAdmim;
    char dvfmEvsUmlAdimimPassword [DVFM_EVS_UML_PASSWORD_BUFFER_SIZE];
    char dvfmEvsUmlConfirmAdimimPassword [DVFM_EVS_UML_PASSWORD_BUFFER_SIZE];
    char *dvfmEvsUmlPointerPassword;
    char dvfmEvsUmlArgvLongOption [15];

    dvfmEvsUmlUserDataType  dvfmEvsUmlDataUser;
    dvfmEvsUmlConfigurationOptionsType dvfmEvsUmlSettings;
    dvfmEvsUmlErrorType dvfmEvsUmlReturnCode;

    dvfmEvsUmlBool dvfmEvsUmlOptionLong = dvfmEvsUmlFalse;

    if(argc < DVFM_EVS_UML_MINIMUM_NUMBER_ARGUMENTS)
    {
        /* error */
        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlShortArgument, dvfmEvsUmlLanguage));
        exit(DVFM_EVS_UML_INVALID_NUMBER_ARGUMENTS_SHORT);
    }

    if(argc > DVFM_EVS_UML_MAXIMUM_NUMBER_ARGUMENTS)
    {
        /* error */
        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLongtArgument, dvfmEvsUmlLanguage));
        exit(DVFM_EVS_UML_INVALID_NUMBER_ARGUMENTS_LONG);
    }

    if(argv[1][0] != '-')
    {
        /* error */
        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidPositionOptions, dvfmEvsUmlLanguage));
        exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
    }

    if(argv[1][1] == '-')
    {
       strcpy(dvfmEvsUmlArgvLongOption, &argv [1][2]);
       dvfmEvsUmlOptionLong = dvfmEvsUmlTrue;
    }

    dvfmEvsUmlCurrentOption = getopt_long(argc, argv, dvfmEvsUmlShortOption, dvfmEvsUmlLongOption, NULL);

    switch (dvfmEvsUmlCurrentOption)
    {
        case 'h':
        
            /* DvfmEvsUmlShowCliHelp */

            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_SHOW_CLI_HELP_H)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[0].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:

                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }

                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;
                
                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }
            }

            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_SHOW_CLI_HELP_H)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }

            DvfmEvsUmlShowCliHelp ( NULL, dvfmEvsUmlLanguage);
        
        break;

        case 'o':
        
            /* DvfmEvsUmlShowConfigurationValues */

            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_SHOW_CONFIGURATION_VALUES_O)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[1].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:

                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }

                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;
                
                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }
        
            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_SHOW_CONFIGURATION_VALUES_O)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }
        
        break;

        case 'N':

            /* DvfmEvsUmlRunNcursesInterface */  

            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_RUN_NCURSES_INTERFACE_N)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[2].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;

                case dvfmEvsUmlIndexUser:
                    
                    dvfmEvsUmlUser = dvfmEvsUmlValueSubOption;

                    break;
                
                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }  
        
            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_RUN_NCURSES_INTERFACE_N)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }
        
        break;
        
        case 'C':
            
            /* DvfmEvsUmlAddUser */ 

            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_ADD_USER_C)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[3].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;

                case dvfmEvsUmlIndexUsername:

                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlNickname = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexConfirmUsername:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlConfirmNickname = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexEmail:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlEmail = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexConfirmEmail:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlConfirmEmail = dvfmEvsUmlValueSubOption;

                    break;
                
                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }

            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_ADD_USER_C)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }

            /* user check to see if he is the administrator */
        
            dvfmEvsUmlIdAdmim = strtoul( DVFM_EVS_UML_ADMINISTRATOR_USER_IDENTIFIER, &dvfmEvsUmlValidation, 10);

            if(*dvfmEvsUmlValidation != DVFM_EVS_UML_EOS)
            {
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlConvertAdmimId, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_CONVERT_ADMINISTRATOR_ID);
            }

            if(dvfmEvsUmlIdAdmim != getuid())
            {
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidId, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_ID);
            }

            /* get password */

            printf("%s:\n", DvfmEvsUmlGetCliUserInterfaceMessage ( dvfmEvsUmlPassword, dvfmEvsUmlLanguage));

            strcpy (dvfmEvsUmlAdimimPassword, (dvfmEvsUmlPointerPassword = getpass ("")));

            printf("%s:\n", DvfmEvsUmlGetCliUserInterfaceMessage ( dvfmEvsUmlConfirmationPassword, dvfmEvsUmlLanguage));

            strcpy( dvfmEvsUmlConfirmAdimimPassword, (dvfmEvsUmlPointerPassword = getpass("")));

            memset( dvfmEvsUmlPointerPassword, 0x00, DVFM_EVS_UML_MAX_SIZE_PASSWORD);

            /* put user information in a struct to pass to the function */

            dvfmEvsUmlDataUser.dvfmEvsUmlConfirmNickname = dvfmEvsUmlConfirmNickname;
            dvfmEvsUmlDataUser.dvfmEvsUmlEmail = dvfmEvsUmlEmail;
            dvfmEvsUmlDataUser.dvfmEvsUmlConfirmEmail = dvfmEvsUmlConfirmEmail;

            strcpy(dvfmEvsUmlDataUser.dvfmEvsUmlNickname, dvfmEvsUmlNickname);
            strcpy(dvfmEvsUmlDataUser.dvfmEvsUmlPassword, dvfmEvsUmlAdimimPassword);
            strcpy(dvfmEvsUmlDataUser.dvfmEvsUmlConfirmPassword, dvfmEvsUmlConfirmAdimimPassword);

            strcpy(dvfmEvsUmlDataUser.dvfmEvsUmlProfile, "\0");

            /* Populates the structure with the configuration information */

            dvfmEvsUmlReturnCode = DvfmEvsUmlGetConfigurationOptionsValues ( dvfmEvsUmlConfiguration, &dvfmEvsUmlSettings);
            
            if(dvfmEvsUmlReturnCode)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlReturnCode, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_ERROR_FUNCTION_CONFIGURATION_OPTIONS);
            }

            /* Call function */

            dvfmEvsUmlReturnCode = DvfmEvsUmlAddUser ( &dvfmEvsUmlSettings, &dvfmEvsUmlDataUser);

            if(dvfmEvsUmlReturnCode)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlReturnCode, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_ERROR_FUNCTION_ADD_USER);
            }

        break;
        
        case 'a':
        
            /* DvfmEvsUmlAddUser */

            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_ADD_USER_A)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[4].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;

                case dvfmEvsUmlIndexUser:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlUser = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexUsername:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlNickname = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexConfirmUsername:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlConfirmNickname = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexEmail:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlEmail = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexConfirmEmail:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlConfirmEmail = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexProfile:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "administrator") && strcmp( dvfmEvsUmlValueSubOption, "professor") && strcmp( dvfmEvsUmlValueSubOption, "student"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    dvfmEvsUmlProfile = dvfmEvsUmlValueSubOption;

                    break;
                
                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }
        
            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_ADD_USER_A)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }
        
        break;
        
        case 'i':
        
            /* DvfmEvsUmlAddUser */

            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_ADD_USER_I)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[5].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;

                case dvfmEvsUmlIndexUser:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlUser = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexUsername:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlNickname = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexConfirmUsername:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlConfirmNickname = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexEmail:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlEmail = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexConfirmEmail:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlConfirmEmail = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexProfile:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "administrator") && strcmp( dvfmEvsUmlValueSubOption, "professor") && strcmp( dvfmEvsUmlValueSubOption, "student"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    dvfmEvsUmlProfile = dvfmEvsUmlValueSubOption;

                    break;
                
                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }
        
            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_ADD_USER_I)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }
        
        break;
        
        case 't':
        
            /* DvfmEvsUmlAcceptInvite */

            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_ACCEPT_INVITE_T)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[6].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;
                
                case dvfmEvsUmlIndexUser:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlUser = dvfmEvsUmlValueSubOption;

                    break;

                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }
        
            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_ACCEPT_INVITE_T)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }
        
        break;
        
        case 'j':
        
            /* DvfmEvsUmlRejectInvite */

            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_REJECT_INVITE_J)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[7].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;

                case dvfmEvsUmlIndexUser:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlUser = dvfmEvsUmlValueSubOption;

                    break;
                
                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }
        
            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_REJECT_INVITE_J)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }
        
        break;
        
        case 'n':
        
            /* DvfmEvsUmlRequestRegistration */

            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_REQUEST_REGISTRATION_N)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[8].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;

                case dvfmEvsUmlIndexUsername:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlNickname = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexConfirmUsername:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlConfirmNickname = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexEmail:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlEmail = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexConfirmEmail:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlConfirmEmail = dvfmEvsUmlValueSubOption;

                    break;
                
                case dvfmEvsUmlIndexFriendEmail:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlFriendEmail = dvfmEvsUmlValueSubOption;

                    break;

                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }
            
            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_REQUEST_REGISTRATION_N)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }
        
        break;
        
        case 'q':
        
            /* DvfmEvsUmlGetPendingRegistrationRequestsPerUser */

            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_GET_PENDING_REGISTRATION_REQUESTS_PER_USER_Q)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[9].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;

                case dvfmEvsUmlIndexUser:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlUser = dvfmEvsUmlValueSubOption;

                    break;
                
                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }
        
            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_GET_PENDING_REGISTRATION_REQUESTS_PER_USER_Q)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }
        
        break;
        
        case 'Q':
        
            /* DvfmEvsUmlGetPendingRegistrationRequests */

            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_GET_PENDING_REGISTRATION_REQUESTS_Q)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[10].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;

                case dvfmEvsUmlIndexUser:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlUser = dvfmEvsUmlValueSubOption;

                    break;
                
                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }
        
            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_GET_PENDING_REGISTRATION_REQUESTS_Q)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }
        
        break;
        
        case 'v':
        
            /* DvfmEvsUmlApproveRegistrationRequest */

            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_APPROVED_REGISTRATION_REQUEST_V)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[11].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;

                case dvfmEvsUmlIndexUser:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlUser = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexNickname:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlNickname = dvfmEvsUmlValueSubOption;

                    break;
                
                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }
        
            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_APPROVED_REGISTRATION_REQUEST_V)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }
        
        break;
        
        case 'd':
        
            /* DvfmEvsUmlDisapproveRegistrationRequest */


            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_DISAPPROVE_REGISTRATION_REQUEST_D)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[12].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;

                case dvfmEvsUmlIndexUser:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlUser = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexNickname:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlNickname = dvfmEvsUmlValueSubOption;

                    break;
                
                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }
        
            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_DISAPPROVE_REGISTRATION_REQUEST_D)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }
        
        break;
        
        case 'U':
        
            /* DvfmEvsUmlGetUnlockingRequests */


            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_GET_UNLOCKING_REQUESTS_U)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[13].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;

                case dvfmEvsUmlIndexUser:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlUser = dvfmEvsUmlValueSubOption;

                    break;
                
                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }
        
            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_GET_UNLOCKING_REQUESTS_U)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }
        
        break;
        
        case 'l':
        
            /* DvfmEvsUmlLockUserAccount */

            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_LOCK_USER_ACCOUNT_L)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[14].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;

                case dvfmEvsUmlIndexUser:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlUser = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexNickname:
                    
                    dvfmEvsUmlNickname = dvfmEvsUmlValueSubOption;

                    break;
                
                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }
        
            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_LOCK_USER_ACCOUNT_L)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }
        
        break;
        
        case 'u':
        
            /* DvfmEvsUmlUnlockUserAccount */

            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_UNLOCK_USER_ACCOUNT_U)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[15].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;

                case dvfmEvsUmlIndexUser:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlUser = dvfmEvsUmlValueSubOption;

                    break;
                
                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }
        
            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_UNLOCK_USER_ACCOUNT_U)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }
        
        break;
        
        case 'p':
        
            /* DvfmEvsUmlChangeUserPassword */

            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_CHANGE_USER_PASSWORD_P)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[16].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;

                case dvfmEvsUmlIndexUser:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlUser = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexNickname:
                    
                    dvfmEvsUmlNickname = dvfmEvsUmlValueSubOption;

                    break;
                
                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }
        
            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_CHANGE_USER_PASSWORD_P)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }
        
        break;
        
        case 'r':
        
            /* DvfmEvsUmlResetUserPassword */

            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_RESET_USER_PASSWORD_R)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[17].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;

                case dvfmEvsUmlIndexUser:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlUser = dvfmEvsUmlValueSubOption;

                    break;
                
                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }
        
            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_RESET_USER_PASSWORD_R)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }
        
        break;
        
        case 'm':
        
            /* DvfmEvsUmlChangeUserName */

            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_CHANGE_USER_NAME_M)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[18].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;

                case dvfmEvsUmlIndexUsername:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlNickname = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexConfirmUsername:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlConfirmNickname = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexUser:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlUser = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexNickname:
                    
                    dvfmEvsUmlNickname = dvfmEvsUmlValueSubOption;

                    break;
                
                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }
        
            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_CHANGE_USER_NAME_M)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }
        
        break;
        
        case 'e':
        
            /* DvfmEvsUmlChangeUserEmail */

            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_CHANGE_USER_EMAIL_E)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[19].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;

                case dvfmEvsUmlIndexUser:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlUser = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexEmail:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlEmail = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexConfirmEmail:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlConfirmEmail = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexNickname:
                    
                    dvfmEvsUmlNickname = dvfmEvsUmlValueSubOption;

                    break;

                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }
        
            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_CHANGE_USER_EMAIL_E)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }
        
        break;
        
        case 'c':
        
            /* DvfmEvsUmlConfirmEmailChange */

            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_CONFIRM_EMAIL_CHANGE_C)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[20].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;
                    break;

                case dvfmEvsUmlIndexUser:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlUser = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexNickname:
                    
                    dvfmEvsUmlNickname = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexKey:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlKey = dvfmEvsUmlValueSubOption;

                    break;
                
                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }
        
            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_CONFIRM_EMAIL_CHANGE_C)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }
        
        break;
        
        case 'g':
        
            /* DvfmEvsUmlChangeUserProfile */

            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_CHANGE_USER_PROFILE_G)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[21].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;

                case dvfmEvsUmlIndexUser:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlUser = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexNickname:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    dvfmEvsUmlNickname = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexProfile:
                    
                    dvfmEvsUmlMandatorySubOptionOccurs++;
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "administrator") && strcmp( dvfmEvsUmlValueSubOption, "professor") && strcmp( dvfmEvsUmlValueSubOption, "student"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    dvfmEvsUmlProfile = dvfmEvsUmlValueSubOption;

                    break;
                
                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }
        
            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_CHANGE_USER_PROFILE_G)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }
        
        break;
        
        case 's':
        
            /* DvfmEvsUmlGetUsers */

            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_GET_USERS_S)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[22].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;
                
                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }
        
            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_GET_USERS_S)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }
        
        break;
        
        case 'S':
        
            /* DvfmEvsUmlSearchUsers */

            if(argc - 2 < DVFM_EVS_UML_REQUIRED_SUBOPTION_SEARCH_USERS_S)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlFewSubOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_NUMBER_SUB_OPTIONS_SHORT);
            }

            if(strcmp( dvfmEvsUmlArgvLongOption, dvfmEvsUmlLongOption[23].name) && dvfmEvsUmlOptionLong)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_INVALID_POSITION_OPTION);
            }

            for(dvfmEvsUmlIndexArgument = DVFM_EVS_UML_START_SUB_OPTIONS; dvfmEvsUmlIndexArgument < argc; dvfmEvsUmlIndexArgument++)
            {
                dvfmEvsUmlCurrentArgument = argv[dvfmEvsUmlIndexArgument];

                dvfmEvsUmlIndexNameSubOption= getsubopt(&(dvfmEvsUmlCurrentArgument), dvfmEvsUmlSubOption, &dvfmEvsUmlValueSubOption);

                switch (dvfmEvsUmlIndexNameSubOption)
                {
                case dvfmEvsUmlIndexConfiguration:

                    dvfmEvsUmlConfiguration = dvfmEvsUmlValueSubOption;
                    
                    break;

                case dvfmEvsUmlIndexLanguage:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") && strcmp( dvfmEvsUmlValueSubOption, "english"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "portuguese") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlPortuguese;

                    if(strcmp( dvfmEvsUmlValueSubOption, "english") == 0)
                        dvfmEvsUmlLanguage = dvfmEvsUmlEnglish;

                    break;

                case dvfmEvsUmlIndexUsername:
                    
                    dvfmEvsUmlNickname = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexEmail:
                    
                    dvfmEvsUmlEmail = dvfmEvsUmlValueSubOption;

                    break;

                case dvfmEvsUmlIndexProfile:
                    
                    if(strcmp( dvfmEvsUmlValueSubOption, "administrator") && strcmp( dvfmEvsUmlValueSubOption, "professor") && strcmp( dvfmEvsUmlValueSubOption, "student") && strcmp( dvfmEvsUmlValueSubOption, "administrator-professor") && strcmp( dvfmEvsUmlValueSubOption, "administrator-student") && strcmp( dvfmEvsUmlValueSubOption, "professor-student") && strcmp( dvfmEvsUmlValueSubOption, "administrator-professor-student"))
                    {
                        /* error */
                        printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidSubOption, dvfmEvsUmlLanguage));
                        exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);
                    }
                    
                    dvfmEvsUmlProfile = dvfmEvsUmlValueSubOption;

                    break;
                
                default:

                    /* error */
                    printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlMissingSubOptions, dvfmEvsUmlLanguage));
                    exit(DVFM_EVS_UML_INVALID_SUB_OPTIONS);

                    break;
                }

            }
        
            if(dvfmEvsUmlMandatorySubOptionOccurs < DVFM_EVS_UML_REQUIRED_SUBOPTION_SEARCH_USERS_S)
            {
                /* error */
                printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlLackCompulsorySubOption, dvfmEvsUmlLanguage));
                exit(DVFM_EVS_UML_LACK_COMPULSORY_SUBOPTION);
            }
        
        break;
        
        default:

            /* error */
            printf("%s\n", DvfmEvsUmlGetCliErrorMessage ( dvfmEvsUmlInvalidOptions, dvfmEvsUmlLanguage));
            exit(DVFM_EVS_UML_INVALID_OPTIONS);

        break;

    }

}

/* $RCSfile: dvfmEvsUml.c,v $ */