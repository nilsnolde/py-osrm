@ECHO OFF
SETLOCAL
SET EL=0

SET DATA_DIR=%CD%

CD %DATA_DIR%
IF %ERRORLEVEL% NEQ 0 GOTO ERROR

SET test_region=monaco
SET test_region_ch=ch\monaco
SET test_region_corech=corech\monaco
SET test_region_mld=mld\monaco
SET test_osm=%test_region%.osm.pbf
python -m osrm extract -p %DATA_DIR%\profiles\car.lua %DATA_DIR%\monaco.osm.pbf
IF %ERRORLEVEL% NEQ 0 GOTO ERROR

MKDIR ch
XCOPY %test_region%.osrm.* ch\
XCOPY %test_region%.osrm ch\
MKDIR corech
XCOPY %test_region%.osrm.* corech\
XCOPY %test_region%.osrm corech\
MKDIR mld
XCOPY %test_region%.osrm.* mld\
XCOPY %test_region%.osrm mld\
python -m osrm contract %test_region_ch%.osrm
python -m osrm contract --core 0.8 %test_region_corech%.osrm
python -m osrm partition %test_region_mld%.osrm
python -m osrm customize %test_region_mld%.osrm
IF %ERRORLEVEL% NEQ 0 GOTO ERROR

:ERROR
ECHO ~~~~~~~~~~~~~~~~~~~~~~ ERROR %~f0 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ECHO ERRORLEVEL^: %ERRORLEVEL%
SET EL=%ERRORLEVEL%

:DONE
ECHO ~~~~~~~~~~~~~~~~~~~~~~ DONE %~f0 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~

EXIT /b %EL%
