get_version()
{
    local __base=${1:-1}
    echo $((`git rev-list --branches|wc -l` + $__base))
}

VER_FILE=version.in
echo -n " .equ BUILD_VERSION, " > $VER_FILE
get_version 2 >> $VER_FILE