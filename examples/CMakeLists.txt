

ADD_SUBDIRECTORY(simulators)


FILE(COPY "${EXAMPLES_PROJECTS_PATH}" 
     DESTINATION "${BUILD_OUTPUT_PATH}/${EXAMPLES_INSTALL_PATH}")
       
       
OPENFLUID_ADD_TEST(NAME examples-Primitives 
                   COMMAND "${BIN_OUTPUT_PATH}/${OPENFLUID_CMD_APP}" 
                              "-i" "${CMAKE_CURRENT_SOURCE_DIR}/projects/Primitives/IN"
                              "-o" "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.Examples.Primitives" 
                    PRE_TEST REMOVE_DIRECTORY "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.Primitives"
                    POST_TEST CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.Examples.Primitives/openfluid-messages.log"
                              CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.Examples.Primitives/examples.primitives.unitsA.prod_ofware-sim.log"
                              CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.Examples.Primitives/examples.primitives.unitsB.prod_ofware-sim.log"
                              CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.Examples.Primitives/fullA_unitsA1_var1.csv"
                              CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.Examples.Primitives/fullB_unitsB2_var5.csv"
                   )
                   
                   
OPENFLUID_ADD_TEST(NAME examples-Manhattan 
                   COMMAND "${BIN_OUTPUT_PATH}/${OPENFLUID_CMD_APP}" 
                              "-i" "${CMAKE_CURRENT_SOURCE_DIR}/projects/Manhattan/IN"
                              "-o" "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.Examples.Manhattan" 
                    PRE_TEST REMOVE_DIRECTORY "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.Manhattan"
                    POST_TEST CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.Examples.Manhattan/openfluid-messages.log"
                              CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.Examples.Manhattan/manhattan-anim.kmz"
                              CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.Examples.Manhattan/examples.RU11.stock.pdf"
                              
                   )

                   
OPENFLUID_ADD_TEST(NAME examples-Firespread 
                   COMMAND "${BIN_OUTPUT_PATH}/${OPENFLUID_CMD_APP}" 
                              "-i" "${CMAKE_CURRENT_SOURCE_DIR}/projects/Firespread/IN"
                              "-o" "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.Examples.Firespread"
                    PRE_TEST REMOVE_DIRECTORY "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.Firespread"
                    POST_TEST CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.Examples.Firespread/openfluid-messages.log"
                              CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.Examples.Firespread/firespread-anim.kmz"                                                            
                   )                   
                                                       

INSTALL(DIRECTORY "projects/" 
        DESTINATION "${EXAMPLES_PROJECTS_INSTALL_PATH}" PATTERN ".svn" EXCLUDE)
