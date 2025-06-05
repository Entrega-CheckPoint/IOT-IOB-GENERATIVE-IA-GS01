FROM nodered/node-red:latest

USER root

RUN apk add --no-cache libaio unzip

COPY instantclient-basiclite-linux.x64-21.11.0.0.0dbru.zip /opt/oracle/

RUN cd /opt/oracle && \
    unzip instantclient-basiclite-linux.x64-21.11.0.0.0dbru.zip && \
    rm instantclient-basiclite-linux.x64-21.11.0.0.0dbru.zip && \
    echo "/opt/oracle/instantclient_21_11" > /etc/ld.so.conf.d/oracle-instantclient.conf && \
    ldconfig

USER node-red
