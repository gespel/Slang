FROM gespel/debian-base:latest

COPY . .

RUN ./build.sh

ENTRYPOINT ["./test"]
