while true
do
    ps -ef | grep "./bin/server 1206 ../web2/docs" | grep -v "grep"
    if [ "$?" -eq 1 ]
        then
        ./bin/server 80 ../web2/docs #启动应用，修改成自己的启动应用脚本或命令
        echo "server has been restarted!"
    else
        echo "server already started!"
    fi
    sleep 10
done
