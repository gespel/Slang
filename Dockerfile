FROM archlinux:latest

# Pakete installieren
RUN pacman -Sy --noconfirm \
      cmake \
      make \
      automake \
      gcc \
      git \
#      linux-headers \
      bash \
      meson zsh

RUN chsh -s /bin/zsh

RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

ENTRYPOINT ["sleep", "infinity"]