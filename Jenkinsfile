pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
              script {
                      try {
                        echo 'Building..'
                      } catch (Exception e) {
                          slackSend color: "danger", message: "Build failed: " + env.BRANCH_NAME
                      }
                }
                slackSend color: "good", message: "build succeeded: " + env.BRANCH_NAME
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
