### MAIN NODE

NODE_ARCHITECTURE="armv7"

mkdir -p /opt/prometheus
cd /opt/prometheus

wget "https://github.com/prometheus/prometheus/releases/download/v2.31.1/prometheus-2.31.1.linux-$NODE_ARCHITECTURE.tar.gz"
tar -zxvf prometheus-2.31.1.linux-$NODE_ARCHITECTURE.tar.gz && rm -rf prometheus-2.31.1.linux-$NODE_ARCHITECTURE.tar.gz
mv prometheus-2.31.1.linux-$NODE_ARCHITECTURE/ prometheus/
chown pi:pi -R /opt/prometheus/

cat <<EOF > /etc/systemd/system/prometheus.service
[Unit]
Description=Prometheus Server
Documentation=https://prometheus.io/docs/introduction/overview/
After=network-online.target

[Service]
User=pi
Restart=on-failure

ExecStart=/opt/prometheus/prometheus \
  --config.file=/opt/prometheus/prometheus.yml \
  --storage.tsdb.path=/opt/prometheus/data

[Install]
WantedBy=multi-user.target
EOF

sudo systemctl enable prometheus
sudo systemctl start prometheus