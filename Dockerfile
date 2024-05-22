FROM ubuntu:18.04 as builder

RUN apt-get update -qq && \
    apt-get install -y --no-install-recommends \
      software-properties-common && \
    add-apt-repository -y ppa:team-gcc-arm-embedded/ppa && \
    apt-get update -qq && \
    apt-get install -y --no-install-recommends \
      git make cmake python3 \
      gcc-arm-embedded && \
    apt-get autoremove -y && \
    apt-get clean -y && \
    rm -rf /var/lib/apt/lists/*

# Project sources volume should be mounted at /app
COPY . C:/Users/drvig/OneDrive/Desktop/microbit-v2-samples
WORKDIR C:/Users/drvig/OneDrive/Desktop/microbit-v2-samples

RUN python3 build.py

FROM scratch AS export-stage
COPY --from=builder C:/Users/drvig/OneDrive/Desktop/microbit-v2-samples/MICROBIT.bin .
COPY --from=builder c:/Users/drvig/OneDrive/Desktop/microbit-v2-samples/MICROBIT.hex .

ENTRYPOINT ["bin/bash"]
