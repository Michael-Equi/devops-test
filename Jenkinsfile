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
              script {
                      try {
                        echo 'Building..'
                      } catch (Exception e) {
                          slackSend color: "danger", message: "Build failed on " + determineRepoName() + " on branch " + env.BRANCH_NAME + " on commit " + "${GIT_COMMIT}" + " with message " + env.COMMIT_MESSAGE + " at time ${new Date()}"
                          sh false
                      }
                }
                slackSend color: "good", message: "Build succeeded on " + determineRepoName() + " on branch " + env.BRANCH_NAME + " on commit " + "${GIT_COMMIT}" + " with message " + env.COMMIT_MESSAGE + " at time ${new Date()}"
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
