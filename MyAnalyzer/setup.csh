set DIR=`pwd`
setenv TNM_PATH ${DIR}
setenv PYTHONPATH ${TNM_PATH}/python:${PYTHONPATH}
setenv LD_LIBRARY_PATH ${TNM_PATH}/lib:${LD_LIBRARY_PATH}
echo "TNM_PATH=${TNM_PATH}"
