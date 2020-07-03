pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
              script {
                      try {
                        echo 'Building..'
                      } catch (Exception e) {
                          slackSend color: "danger", message: "build failed"
                      }
                }
                slackSend color: "good", message: "build succeeded"
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
