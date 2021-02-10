# $strString = "Hello World"
# write-host $strString

python -u D:/renode/tests/run_tests.py                                             `
       --css-file C:/Program` Files/Renode/tests/robot.css                         `
       --robot-framework-remote-server-full-directory C:/Program` Files/Renode/bin `
       -t "../test/tests.yaml"                                                     `
       -r ../test_results --variable PATH:$PWD