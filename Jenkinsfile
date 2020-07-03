pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
              script {
                      try {
                        echo 'Building..'
                        sh false
                      } catch (Exception e) {
                          slackSend color: "danger", message: "Build failed on branch " + env.BRANCH_NAME + " at time ${new Date()}"
                          sh false
                      }
                }
                slackSend color: "good", message: "build succeeded on branch " + env.BRANCH_NAME + " at time ${new Date()}"
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
