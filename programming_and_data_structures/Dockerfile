FROM ubuntu:latest

# Install compiler and valgrind
RUN apt-get update && apt-get install -y \
    build-essential \
    valgrind \
    && rm -rf /var/lib/apt/lists/*

# Default working directory (where your code will live)
WORKDIR /workspace
