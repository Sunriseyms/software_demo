#!/bin/sh

cgroup_test() {
    my_cgroup_path="/sys/fs/cgroup/cpu/my_cgroup"
    # creat cgroup
    if [ ! -d ${my_cgroup_path} ];then
        sudo mkdir  ${my_cgroup_path}
    fi

    # run app
    ../cgroup_demo/cgroup_demo $1 &
    sleep 1
    app_pid=`ps -ef | grep cgroup_demo | grep -v grep | grep -v cgroup_demo_start | awk '{print $2}'`
    echo ${app_pid}
    sudo bash -c "echo ${app_pid} > ${my_cgroup_path}/tasks"
    sudo bash -c "echo 50000 > ${my_cgroup_path}/cpu.cfs_quota_us"

    # check pid
    cat /sys/fs/cgroup/cpu/my_cgroup/tasks
}


mount | grep cgroup | grep -v grep
is_support_cgroup=0
if [ $? -ne 0 ];then
    echo "this system is not support cgroup"
else
    is_support_cgroup=1
    echo "this system support cgroup"
fi
echo ${is_support_cgroup}

if [ ${is_support_cgroup} -eq 1 ];then
    cgroup_test $1
fi
