FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    gcc \
    make \
    libpcap-dev \
    tcpdump \
    python3 \
    python3-pip \
    && pip3 install matplotlib scapy \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . /app

RUN make build

CMD ["/bin/bash"]