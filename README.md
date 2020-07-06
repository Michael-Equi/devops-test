# devops-test
Testing revolutionary devops techniques

## Banners

[![CodeFactor](https://www.codefactor.io/repository/github/michael-equi/devops-test/badge)](https://www.codefactor.io/repository/github/michael-equi/devops-test)

master

[![Build Status](http://64.113.104.119:6268/buildStatus/icon?job=devops-test%2Fmaster)](http://64.113.104.119:6268/job/devops-test/job/master/)

[![Coverage Status](https://coveralls.io/repos/github/Michael-Equi/devops-test/badge.svg?branch=master)](https://coveralls.io/github/Michael-Equi/devops-test?branch=master)

development

[![Build Status](http://64.113.104.119:6268/buildStatus/icon?job=devops-test%2Fdevelopment)](http://64.113.104.119:6268/job/devops-test/job/development/)


[![Coverage Status](https://coveralls.io/repos/github/Michael-Equi/devops-test/badge.svg?branch=development)](https://coveralls.io/github/Michael-Equi/devops-test?branch=development)

## Goal 

From every github commit run a test in Jenkins that builds the ROS2 node and runs a gtest unit test script as well as a "integration" test that runs the node itself and scans the ROS2 topic. Build the docker file in Jenkins and push to Github. Update status of Dockerfile build, Jenkins build, and Jenkins tests banners. Create a coveragage report using gcov and push to codecov in order to include a banner that keeps track of unit test coverge. Find/develop system to report linter violations and crusty code that needs to be fixed. Linters are ament_cpplin, ament_uncrustify, and ament_cppcheck.  

## Configuration
Use the VCS tool in order to import dependencies `vcs import < tool/deps.repos`


## Running Jenkins

First Container

`docker container run --name jenkins-docker --rm --detach \
  --privileged --network jenkins --network-alias docker \
  --env DOCKER_TLS_CERTDIR=/certs \
  --volume jenkins-docker-certs:/certs/client \
  --volume jenkins-data:/var/jenkins_home \
  --publish 2376:2376 docker:dind`


Second Container

`docker container run --name jenkins-blueocean --rm --detach \
  --network jenkins --env DOCKER_HOST=tcp://docker:2376 \
  --env DOCKER_CERT_PATH=/certs/client --env DOCKER_TLS_VERIFY=1 \
  --volume jenkins-data:/var/jenkins_home \
  --volume jenkins-docker-certs:/certs/client:ro \
  --publish 6268:8080 --publish 50000:50000 jenkinsci/blueocean`


Read more at https://www.jenkins.io/doc/book/installing/
