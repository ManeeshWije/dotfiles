if status is-interactive
    # Commands to run in interactive sessions can go here
end

fish_add_path /opt/homebrew/bin

set fish_greeting                                 
set -gx TERM "xterm-256color"                      
set -gx EDITOR "nvim" 

alias vim='nvim'

alias addup='git add -u'
alias addall='git add .'
alias branch='git branch'
alias checkout='git checkout'
alias clone='git clone'
alias commit='git commit -am'
alias fetch='git fetch'
alias pull='git pull'
alias push='git push'
alias tag='git tag'
alias newtag='git tag -a'
alias stats='git status'

alias ..='cd ..'
alias ...='cd ../..'
alias .3='cd ../../..'
alias .4='cd ../../../..'
alias .5='cd ../../../../..'

alias rr='curl -s -L https://raw.githubusercontent.com/keroserene/rickrollrc/master/roll.sh | bash'

#colorscript random
pfetch
starship init fish | source
fish_add_path /opt/homebrew/opt/llvm/bin
