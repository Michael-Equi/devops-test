String determineRepoName() {
return scm.getUserRemoteConfigs()[0].getUrl().tokenize('/').last().split("\\.")[0]
}

pipeline {
    agent any

    options {
      timeout(time: 1, unit: 'HOURS')
    }

    environment {
      COMMIT_MESSAGE = sh (
                          script: 'git log --format=%B -n 1 \"${GIT_COMMIT}\"',
                          returnStdout: true
                          ).trim()
    }

    stages {
        stage('Build') {
            steps {
              echo "Building..."
            }
            post {
                    always {
                      echo 'One way or another, I have finished'
                    }
                    success {
                      slackSend color: "good", message: "Build succeeded on " + determineRepoName() + " on branch " + env.BRANCH_NAME + " on commit " + "${GIT_COMMIT}" + " with message \"" + env.COMMIT_MESSAGE + "\" at time ${new Date()}"
                    }
                    unstable {
                        echo 'I am unstable :/'
                    }
                    failure {
                      slackSend color: "danger", message: "Build failed on " + determineRepoName() + " on branch " + env.BRANCH_NAME + " on commit " + "${GIT_COMMIT}" + " with message \"" + env.COMMIT_MESSAGE + "\" at time ${new Date()}"
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
