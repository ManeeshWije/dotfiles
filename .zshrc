zstyle ':completion:*' list-colors "${(@s.:.)LS_COLORS}"
autoload -Uz compinit
compinit

export NVM_DIR=~/.nvm
source $(brew --prefix nvm)/nvm.sh
export TERM="xterm-256color"
export EDITOR='nvim'

# Shortcuts
bindkey -v
bindkey '^R' history-incremental-search-backward

# git
alias addup='git add -u'
alias addall='git add .'
alias branch='git branch'
alias checkout='git checkout'
alias clone='git clone'
alias commit='git commit -m'
alias fetch='git fetch'
alias merge-'git merge'
alias pull='git pull origin'
alias push='git push origin'
alias stats='git status'  # 'status' is protected name so using 'stats' instead
alias tag='git tag'
alias newtag='git tag -a'

alias luamake=/Users/maneesh/lua-language-server/3rd/luamake/luamake

# Remove autocomplete lag zsh->git
__git_files () { 
    _wanted files expl 'local files' _files     
}
export PATH="/opt/homebrew/opt/llvm/bin:$PATH"

eval "$(starship init zsh)"
