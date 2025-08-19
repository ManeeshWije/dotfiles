zstyle ':completion:*' list-colors "${(@s.:.)LS_COLORS}"
autoload -Uz compinit; compinit

if [[ "$OSTYPE" == "darwin"* ]]; then
    fpath+=("$(brew --prefix)/share/zsh/site-functions")
fi

export TERM="xterm-256color"
export EDITOR='nvim'
export VISUAL="nvim"
export HISTFILE=~/.zsh_history
export HISTSIZE=10000
export SAVEHIST=10000

setopt appendhistory
setopt sharehistory
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
alias pacupdate='sudo pacman -Syu && yay -Syu'
alias paccache='sudo pacman -Scc && yay -Scc'
alias pacdelete='pacman -Qtdq | sudo pacman -Rns -'
alias o="xdg-open"
alias z="zathura"
alias air='$(go env GOPATH)/bin/air'
alias y="yazi"
alias k="kubectl"
alias todo='nvim "$HOME/Documents/personal-notes/todo.md"'

if [[ "$OSTYPE" == "darwin"* ]]; then
    export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
    export PATH="$PATH:/Applications/Docker.app/Contents/Resources/bin/:/Users/maneesh/Library/Python/3.11/bin:/opt/homebrew/opt/postgresql@15/bin:/Users/maneesh/.config/scripts/"
fi

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    export PATH="$HOME/.config/scripts:$HOME/.cargo/env:$HOME/.dotnet/tools:/usr/local/go/bin:$HOME/.local/bin:$PATH"
fi

export NVM_DIR="$HOME/.nvm"
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"  # This loads nvm
. "$HOME/.cargo/env"

source <(fzf --zsh)
source <(kubectl completion zsh)

eval "$(starship init zsh)"
