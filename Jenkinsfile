pipeline {
  agent { dockerfile {args '-u root:root'} }

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
              sh "/tools/setup.sh"
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
