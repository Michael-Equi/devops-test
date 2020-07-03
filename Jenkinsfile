String determineRepoName() {
return scm.getUserRemoteConfigs()[0].getUrl().tokenize('/').last().split("\\.")[0]
}

pipeline {
  agent { dockerfile true }

    options {
      timeout(time: 1, unit: 'HOURS')
    }

    environment {
      COMMIT_MESSAGE = sh (
                          script: 'git log --format=%B -n 1 \"${GIT_COMMIT}\"',
                          returnStdout: true
                          ).trim()
      // This registry is important for removing the image after the tests
      registry = "bytesrobotics/test-node"
    }

    stages {
        stage('Build') {
            steps {
              // script {
              //   dockerfile.image("${GIT_COMMIT}").inside("""--entrypoint='/bin/bash'""") {
              //     echo "Building..."
              //     sh "ls"
              //     sh "rosc"
              //   }
              // }
              sh "ls /"
              sh "/tools/setup.sh"
              sh "ros2"
            }
            post {
                always {
                  echo 'One way or another, I have finished'
                }
                success {
                  slackSend color: "good", message: "The pipeline ${currentBuild.fullDisplayName} succeeded on commit " + "${GIT_COMMIT}" + " with message \"" + env.COMMIT_MESSAGE + "\" at time ${new Date()}"
                }
                unstable {
                    echo 'I am unstable :/'
                }
                failure {
                  slackSend color: "danger", message: "The pipeline ${currentBuild.fullDisplayName} failed on commit " + "${GIT_COMMIT}" + " with message \"" + env.COMMIT_MESSAGE + "\" at time ${new Date()}"
                }
                changed {
                    echo 'Things were different before...'
                }
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying....'
            }
        }
    }
}
