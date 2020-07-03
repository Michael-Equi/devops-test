FROM osrf/ros2:nightly

COPY ./node /opt/br/node
COPY ./tools /tools
CMD /bin/bash
