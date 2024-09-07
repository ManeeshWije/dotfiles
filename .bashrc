[ -z "$PS1" ] && return

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
set appendhistory
set sharehistory
set incappendhistory
set hist_ignore_all_dups
set hist_save_no_dups
set hist_ignore_dups
set hist_find_no_dups

bind -m vi-insert "\C-l":clear-screen

export TERM="xterm-256color"
export BROWSER='firefox'
export EDITOR='nvim'
export VISUAL="nvim"
export HISTFILE=~/.bash_history
export HISTSIZE=10000
export SAVEHIST=10000
export HISTFILESIZE=2000
export HISTTIMEFORMAT="%F %T "
export HISTCONTROL=ignoredups


# git
alias addup='git add -u'
alias addall='git add .'
alias branch='git branch'
alias checkout='git checkout'
alias clone='git clone'
alias commit='git commit -m'
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
alias sd="cd \$(find $HOME -type d | fzf)"
alias sf="xdg-open \$(find $HOME -type f | fzf)"
alias y='yazi'
alias paccache='sudo pacman -Scc && yay -Scc'
alias pacdelete='pacman -Qtdq | sudo pacman -Rns -'
alias o="xdg-open"
alias z="zathura"

PATH="$HOME/.bun/bin:$HOME/.config/scripts:$HOME/.cargo/env:$PATH"

function git_branch() {
    if [ -d .git ] ; then
        printf "%s" "($(git branch 2> /dev/null | awk '/\*/{print $2}'))";
    fi
}

function bash_prompt(){
    PS1='${debian_chroot:+($debian_chroot)}'${blu}'$(git_branch)'${pur}' \W'${grn}' \$ '${clr}
}

bash_prompt
