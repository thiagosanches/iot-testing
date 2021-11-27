# EXTERNAL NODE
NODE_ARCHITECTURE="armv7"
mkdir -p /opt/node-exporter && cd /opt/node-exporter
wget -O node-exporter.tar.gz "https://github.com/prometheus/node_exporter/releases/download/v1.3.0/node_exporter-1.3.0.linux-$NODE_ARCHITECTURE.tar.gz"
tar -xvf node-exporter.tar.gz --strip-components=1 && rm -f node-exporter.tar.gz

cat <<EOF >  /etc/systemd/system/nodeexporter.service
[Unit]
Description=Prometheus Node Exporter
Documentation=https://prometheus.io/docs/guides/node-exporter/
After=network-online.target

[Service]
User=pi
Restart=on-failure

ExecStart=/opt/node-exporter/node_exporter

[Install]
WantedBy=multi-user.target
EOF

sudo systemctl enable nodeexporter && sudo systemctl start nodeexporter