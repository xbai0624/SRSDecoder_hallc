#source /home/srsdaq/ROOT/bin/thisroot.csh

setenv ET_EVIO /home/daq/coda/2.6.2/Linux-x86_64

setenv GEMVIEW_ET_LIB ${ET_EVIO}/lib
setenv GEMVIEW_ET_INC ${ET_EVIO}/include

setenv PATH ${ROOTSYS}/bin:${PATH}

if (!($?LD_LIBRARY_PATH)) then
  setenv LD_LIBRARY_PATH ${GEMVIEW_ET_LIB}:${ROOTSYS}/lib/root
else
  setenv LD_LIBRARY_PATH ${GEMVIEW_ET_LIB}:${ROOTSYS}/lib/root:${LD_LIBRARY_PATH}
endif
