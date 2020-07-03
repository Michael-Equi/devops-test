String determineRepoName() {
return scm.getUserRemoteConfigs()[0].getUrl().tokenize('/').last().split("\\.")[0]
}

pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
              COMMIT_MESSAGE = sh (
                                      script: 'git log --format=%B -n 1 \"${GIT_COMMIT}\"',
                                      returnStdout: true
                                  ).trim()
              script {
                      try {
                        echo 'Building..'
                      } catch (Exception e) {
                          slackSend color: "danger", message: "Build failed on " + determineRepoName() + " on branch " + env.BRANCH_NAME + " on commit " + "${GIT_COMMIT}" + " with message " + commit_message + " at time ${new Date()}"
                          sh false
                      }
                }
                slackSend color: "good", message: "Build succeeded on " + determineRepoName() + " on branch " + env.BRANCH_NAME + " on commit " + "${GIT_COMMIT}" + " with message " + commit_message + " at time ${new Date()}"
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
