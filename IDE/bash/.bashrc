# ~/.bashrc: executed by bash(1) for non-login shells.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples

# If not running interactively, don't do anything
case $- in
    *i*) ;;
      *) return;;
esac

# don't put duplicate lines or lines starting with space in the history.
# See bash(1) for more options
HISTCONTROL=ignoreboth

# append to the history file, don't overwrite it
shopt -s histappend

# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
HISTSIZE=1000
HISTFILESIZE=2000

# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
shopt -s checkwinsize

# If set, the pattern "**" used in a pathname expansion context will
# match all files and zero or more directories and subdirectories.
#shopt -s globstar

# make less more friendly for non-text input files, see lesspipe(1)
[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"

# set variable identifying the chroot you work in (used in the prompt below)
if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

# set a fancy prompt (non-color, unless we know we "want" color)
case "$TERM" in
    xterm-color|*-256color) color_prompt=yes;;
esac

# uncomment for a colored prompt, if the terminal has the capability; turned
# off by default to not distract the user: the focus in a terminal window
# should be on the output of commands, not on the prompt
force_color_prompt=yes

if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
	# We have color support; assume it's compliant with Ecma-48
	# (ISO/IEC-6429). (Lack of such support is extremely rare, and such
	# a case would tend to support setf rather than setaf.)
	color_prompt=yes
    else
	color_prompt=
    fi
fi

# Define Colors
COLOR_RED="\033[0;31m"
COLOR_YELLOW="\033[0;33m"
COLOR_GREEN="\033[0;32m"
COLOR_LIGHT_GREEN="\033[1;32m"
COLOR_OCHRE="\033[38;5;95m"
COLOR_BLUE="\033[1;34m"
COLOR_WHITE="\033[0;37m"
COLOR_RESET="\033[0m"

function git_color {
    local git_status="$(git status 2> /dev/null)"
    if [[ ! $git_status =~ "working directory clean" ]]; then
        echo -e $COLOR_RED
    elif [[ $git_status =~ "Your branch is ahead of" ]]; then
        echo -e $COLOR_YELLOW
    elif [[ $git_status =~ "nothing to commit" ]]; then
        echo -e $COLOR_GREEN
    else
        echo -e $COLOR_OCHRE
    fi
}

function git_branch {
    local git_status="$(git status 2> /dev/null)"
    local on_branch="On branch ([^${IFS}]*)"
    local on_commit="HEAD detached at ([^${IFS}]*)"

    if [[ $git_status =~ $on_branch ]]; then
        local branch=${BASH_REMATCH[1]}
        echo "($branch)"
    elif [[ $git_status =~ $on_commit ]]; then
        local commit=${BASH_REMATCH[1]}
        echo "($commit)"
    fi
}

if [ "$color_prompt" = yes ]; then
    # PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
    PS1="${debian_chroot:+($debian_chroot)}\[$COLOR_LIGHT_GREEN\]\u\[$COLOR_WHITE\]@\[$COLOR_OCHRE\]\h\[$COLOR_RESET\]:[\[$COLOR_BLUE\]\W\[$COLOR_RESET\]]\[\033[00m\]"
    # PS1='\e[32;1m\u@\e[30;48;5;226m\W\e[0m\$ ' # this will change your prompt format
    # PS1='\e[30;48;5;226m\W\e[0m\$ ' # this will change your prompt format
    # PS1="\[$COLOR_WHITE\]\n[\W]"    # basename of pwd
    PS1+="\[\$(git_color)\]"        # colors git status
    PS1+="\$(git_branch)"           # prints current branch
    PS1+="\[$COLOR_RESET\]\$ "   # '#' for root, else '$'
    #export PS1
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
unset color_prompt force_color_prompt

# If this is an xterm set the title to user@host:dir
case "$TERM" in
xterm*|rxvt*)
    PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
    ;;
*)
    ;;
esac

# enable color support of ls and also add handy aliases
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color=auto'
    #alias dir='dir --color=auto'
    #alias vdir='vdir --color=auto'

    alias grep='grep --color=auto'
    alias fgrep='fgrep --color=auto'
    alias egrep='egrep --color=auto'
fi

# colored GCC warnings and errors
export GCC_COLORS='error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01'

# some more ls aliases
# alias ll='ls -alF'
# alias la='ls -A'
# alias l='ls -CF'

# Add an "alert" alias for long running commands.  Use like so:
#   sleep 10; alert
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'

# Alias definitions.
# You may want to put all your additions into a separate file like
# ~/.bash_aliases, instead of adding them here directly.
# See /usr/share/doc/bash-doc/examples in the bash-doc package.

if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

# enable programmable completion features (you don't need to enable
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
# sources /etc/bash.bashrc).
if ! shopt -oq posix; then
  if [ -f /usr/share/bash-completion/bash_completion ]; then
    . /usr/share/bash-completion/bash_completion
  elif [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
  fi
fi

# checks to see if we are in a windows or linux dir
function isWinDir {
    case $PWD/ in
        /mnt/*) return $(true);;
        *) return $(false);;
    esac
}

# wrap the git command to either run windows git or linux
function git {
    if isWinDir
    then
        git.exe "$@"
    else
        /usr/bin/git "$@"
    fi
}

# added by Miniconda3 installer
export PATH="/home/coolwind/miniconda3/bin:$PATH"
export PATH="/usr/local/gcc-8.2/bin:$PATH"
export PATH="$HOME/.rbenv/bin:$PATH"
export LD_LIBRARY_PATH=/usr/local/gcc-8.2/lib64:$LD_LIBRARY_PATH

# Installl Ruby Gems to ~/gems
export GEM_HOME=$HOME/gems
export PATH=$HOME/gems/bin:$PATH

# For WSL2 (Using IP for vEthernet)
#VETHER_IP=$(/usr/bin/grep nameserver /etc/resolv.conf 2> /dev/null | /usr/bin/tr -s ' ' | /usr/bin/cut -d ' ' -f2)

#VETHER_IP=$(grep -m 1 nameserver /etc/resolv.conf | awk '{print $2; exit;}')

#VETHER_IP=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2; exit;}')
#VETHER_IP=$(/sbin/route -n | /bin/grep "^0.0.0.0" | /bin/tr -s ' ' | /bin/cut -d' ' -f2)
#VETHER_IP=172.18.80.1
#export DISPLAY=$VETHER_IP:0.0
#export DISPLAY=:0
#export LIBGL_ALWAYS_INDIRECT=1
#xhost +local:docker

# Disabled by JoSH 060320
# eval "$(rbenv init -)"

sudo apt update -y && sudo apt upgrade -y && sudo apt autoremove

#docker ps -a -n 10 && docker volume ls
docker ps -a && docker volume ls

lsl(){
	if [ $# -eq 0 ]
	then
		\cd ~ && ls;
	else
		\cd "$1" && ls;
	fi
}
alias cd='lsl'

# >>> conda initialize >>>
# !! Contents within this block are managed by 'conda init' !!
# __conda_setup="$('/home/coolwind/anaconda3/bin/conda' 'shell.bash' 'hook' 2> /dev/null)"
# if [ $? -eq 0 ]; then
#    eval "$__conda_setup"
# else
#    if [ -f "/home/coolwind/anaconda3/etc/profile.d/conda.sh" ]; then
#        . "/home/coolwind/anaconda3/etc/profile.d/conda.sh"
#    else
#        export PATH="/home/coolwind/anaconda3/bin:$PATH"
#    fi
# fi
# unset __conda_setup
# <<< conda initialize <<<
