set(CTEST_PROJECT_NAME "stream_media_transf")
set(CTEST_NIGHTLY_START_TIME "01:00:00 UTC")
set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "192.168.1.14")
set(CTEST_DROP_LOCATION "/cdash/submit.php?project=streammediatransf")
set(CTEST_DROP_SITE_CDASH TRUE)
#set(CTEST_PROJECT_SUBPROJECTS dispatch transfer dispatch_control customer_client customer_server test)
set(CTEST_PROJECT_SUBPROJECTS protocol)
