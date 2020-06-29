# devops-test
Testing revolutionary devops techniques

## Banners

[![CodeFactor](https://www.codefactor.io/repository/github/michael-equi/devops-test/badge)](https://www.codefactor.io/repository/github/michael-equi/devops-test)

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
