# Add this a the top of the module
&include "lib_support_header.inc"

#...

MAIN
   DEFINE ret_val INTEGER
   SUPPORT_INIT(MODULE_)
   CALL main_init()
   CALL main_program() RETURNING ret_val
   CALL main_cleanup()
   SUPPORT_EXIT_PROGRAM_WITH_CLEANUP(ret_val)
END MAIN
CLASSIC_INTROSPECT(NULL)

PRIVATE FUNCTION main_init()
END FUNCTION

PUBLIC FUNCTION main_cleanup()
END FUNCTION

PRIVATE FUNCTION main_program()
END MAIN
