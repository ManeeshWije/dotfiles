[ -z "$PS1" ] && return
[ -f ~/.fzf.bash ] && source ~/.fzf.bash

eval "$(fzf --bash)"

blk='\[\033[01;30m\]'   # Black
red='\[\033[01;31m\]'   # Red
grn='\[\033[01;32m\]'   # Green
ylw='\[\033[01;33m\]'   # Yellow
blu='\[\033[01;34m\]'   # Blue
pur='\[\033[01;35m\]'   # Purple
cyn='\[\033[01;36m\]'   # Cyan
wht='\[\033[01;37m\]'   # White
clr='\[\033[00m\]'      # Reset

set -o vi
export HISTCONTROL=ignoredups:erasedups
export HISTSIZE=100000
export HISTFILESIZE=100000
shopt -s histappend
bind -m vi-insert "\C-l":clear-screen
export PROMPT_COMMAND="history -a; history -c; history -r; $PROMPT_COMMAND"

export TERM="xterm-256color"
export BROWSER='firefox'
export EDITOR='nvim'
export VISUAL="nvim"
export MANPAGER="nvim +Man!"
export GOPATH=$HOME/go
export XDG_SESSION_TYPE=wayland
export XDG_CURRENT_DESKTOP=sway
export XDG_DATA_DIRS=/usr/local/share/:/usr/share/:$HOME/.cache

# git
alias addup='git add -u'
alias addall='git add .'
alias branch='git branch'
alias checkout='git checkout'
alias clone='git clone'
alias commit='git commit'
alias fetch='git fetch'
alias merge='git merge'
alias pull='git pull origin'
alias push='git push origin'
alias stats='git status'  # 'status' is protected name so using 'stats' instead
alias tag='git tag'
alias newtag='git tag -a'

alias ls='ls --color=auto'
alias grep='grep --color=auto'
alias st='syncthing'
alias sd='cd "$(find "$HOME" -maxdepth 7 -type d | fzf || echo "$PWD")"'
alias sf='file=$(find "$HOME" -maxdepth 7 -type f | fzf) && [ -n "$file" ] && xdg-open "$file"'
alias aptupdate='sudo apt update && sudo apt upgrade && yazi_install && ghostty_install'
alias aptdelete='sudo apt autoremove'
alias aptcache='sudo apt-get clean'
alias o="xdg-open"
alias z="zathura"
alias air='$(go env GOPATH)/bin/air'
alias y="yazi"
alias k="kubectl"

PATH="$HOME/.bun/bin:$HOME/.config/scripts:$HOME/.cargo/env:$HOME/.dotnet/tools:/usr/local/go/bin:$HOME/.local/bin:$PATH"

function git_branch() {
    if [ -d .git ] ; then
        printf "%s" "($(git branch 2> /dev/null | awk '/\*/{print $2}'))";
    fi
}

function bash_prompt(){
    PS1='${debian_chroot:+($debian_chroot)}'${blu}'$(git_branch)'${wht}' \W'${grn}' \$ '${clr}
}

bash_prompt
complete -o default -F __start_kubectl k
. "$HOME/.cargo/env"
