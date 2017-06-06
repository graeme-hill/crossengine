rm -rf build
mkdir build && \
pushd build && \
cmake .. && \
make -j9
retcode=$?
popd

if [ $retcode -gt 0 ]
then
	echo "Failed :-("
else
	echo "Passed :-)"
fi
