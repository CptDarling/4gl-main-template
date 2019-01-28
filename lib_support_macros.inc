IMPORT os
IMPORT util
&ifndef LIB_SUPPORT_MACROS
&define LIB_SUPPORT_MACROS

# DISPLAY statement output appears in the VM log.
# ERRORLOG statement output appears in the application error log pgerrlog.
&define logline(txt)          SFMT("%1 [(%6) %5.%4:%3] %2", CURRENT, txt CLIPPED, __LINE__ USING "###&<", os.Path.baseName(__FILE__), base.Application.getProgramName(), fgl_getpid())
&define WRITELOG(txt)         IF fgl_getenv("IMSDEBUG") >= 3 THEN WRITELOG_ALWAYS(txt) END IF
&define WRITELOG_ALWAYS(txt)  CALL ERRORLOG(logline(txt)) DISPLAY logline(txt)
&define WRITELOG_INFO(txt)    DISPLAY logline(txt)
&define RUN_LOG(cmd)          WRITELOG(cmd) RUN cmd
&define WRITE_ERROR(txt)      WRITELOG(txt) ERROR txt

&define WRITE_FGLDIALOG(title,txt,icon)   WRITELOG(txt) CALL fgldialog.fgl_winMessage(title, txt, icon)

&define TIMER_START(title) CALL support_timer_start(title)
&define TIMER_STOP(title)  CALL support_timer_stop(title)
&define TIMER_PRINT(title) CALL support_timer_print(title)
&define TIMER_REPORT       CALL support_timer_report()

&ifndef CLASSIC_INTROSPECT
&define CLASSIC_INTROSPECT(program_state)\
   PUBLIC FUNCTION introspect()\
      DEFINE js STRING\
      LET js = base.Application.getProgramName(), ":\n", util.JSON.format(util.JSON.stringify(program_state))\
      LET js = js\
      RETURN js, js\
   END FUNCTION
&endif # CLASSIC_INTROSPECT

&define SUPPORT_INIT(module_dir) WHENEVER ANY ERROR CALL pgfatal CALL lib_support_init(module_dir, FALSE)
&define SUPPORT_INIT_VAR(module_dir) CALL lib_support_init(module_dir, TRUE)
&define SUPPORT_EXIT_PROGRAM_WITH_CLEANUP(ret_val) CALL lib_support_deinit() EXIT PROGRAM ret_val

# Supports deployment system.
# This macro is to be used in a DIALOG or other user interaction block.
# It uses a timer to check if there is a new deployment and warns the user if there is.
# The UPDATE_TIMEOUT value is usually passed for the timeout.
&define NEW_DEPLOYMENT_WARNING(timeout) ON TIMER timeout CALL support_deployment()

&endif
