FROM fedora:latest

COPY . .
RUN dnf -y install cmake make automake gcc gcc-c++ kernel-devel
RUN mkdir build && cd build && cmake .. && make && cd .. && make
RUN chmod +x test.sh

ENTRYPOINT ["./test.sh"]
