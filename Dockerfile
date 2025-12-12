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
      meson 

# Arbeitsverzeichnis setzen
WORKDIR /app

# Projekt kopieren
COPY . .

# Build
RUN meson setup build
RUN ninja -C build

# Testskript ausführbar machen
RUN chmod +x test.sh

ENTRYPOINT ["sleep", "infinity"]