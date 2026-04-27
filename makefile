CC=gcc
CFLAGS=-Wall -Wextra
LDFLAGS=-lpcap
TARGET=nids

SRC=src/main.c src/parser.c src/detector.c src/logger.c

.PHONY: build up demo test clean bootstrap

build:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

up:
	docker compose up -d --build

demo:
	docker compose exec nids bash scripts/run_demo.sh

test:
	docker compose exec nids bash tests/test_happy_path.sh && \
	docker compose exec nids bash tests/test_negative.sh && \
	docker compose exec nids bash tests/test_empty_pcap.sh && \
	docker compose exec nids bash tests/test_malformed_input.sh && \
	docker compose exec nids bash tests/test_threshold.sh

clean:
	rm -f $(TARGET)

bootstrap: up