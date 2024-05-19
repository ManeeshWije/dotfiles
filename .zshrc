zstyle ':completion:*' list-colors "${(@s.:.)LS_COLORS}"
autoload -Uz compinit
compinit

# if [[ "$OSTYPE" == "linux-gnu"* ]]; then
if [[ "$OSTYPE" == "darwin"* ]]; then
    fpath+=("$(brew --prefix)/share/zsh/site-functions")
fi

export NVM_DIR=~/.nvm
export TERM="xterm-256color"
export EDITOR='nvim'
export VISUAL="nvim"
export HISTSIZE=10000
export SAVEHIST=10000
export HISTDUPE=erase

setopt appendhistory
setopt sharehistory
setopt hist_ignore_space
setopt hist_ignore_all_dups
setopt hist_save_no_dups
setopt hist_ignore_dups
setopt hist_find_no_dups


# Shortcuts
bindkey -v
bindkey '^R' history-incremental-search-backward
bindkey '^p' history-search-backward
bindkey '^n' history-search-forward
bindkey '^H' backward-delete-char
bindkey '^?' backward-delete-char
bindkey -s ^f "tmux-sessionizer\n"

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

alias st='syncthing'


if [[ "$OSTYPE" == "darwin"* ]]; then
    export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
    export PATH="$PATH:/Applications/Docker.app/Contents/Resources/bin/:/Users/maneesh/Library/Python/3.11/bin:/opt/homebrew/opt/postgresql@15/bin:/Users/maneesh/.config/scripts/"
    # bun
    export BUN_INSTALL="$HOME/.bun"
    export PATH="$BUN_INSTALL/bin:$PATH"
fi


autoload -U promptinit; promptinit
prompt pure
