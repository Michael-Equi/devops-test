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

      COVERALLS_REPO_TOKEN = credentials("DEVOPS_TEST_COVERALLS_REPO_TOKEN")

    }

    stages {
        stage('Build') {
            steps {
              echo 'Building..'
              sh "/tools/setup.sh"
            }
            post {
                always {
                  echo 'One way or another, I have finished'
                }
                success {
                  slackSend color: "good", message: "The pipeline ${currentBuild.fullDisplayName} build succeeded on commit " + "${GIT_COMMIT}" + " with message \"" + env.COMMIT_MESSAGE + "\" at time ${new Date()}"
                }
                unstable {
                    echo 'I am unstable :/'
                }
                failure {
                  slackSend color: "danger", message: "The pipeline ${currentBuild.fullDisplayName} build failed on commit " + "${GIT_COMMIT}" + " with message \"" + env.COMMIT_MESSAGE + "\" at time ${new Date()}"
                }
                changed {
                    echo 'Things were different before...'
                }
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
                sh "echo ${env.COVERALLS_REPO_TOKEN}"
                sh "/tools/run_tests.sh ${env.COVERALLS_REPO_TOKEN}"
            }
            post {
                success {
                  slackSend color: "good", message: "The pipeline ${currentBuild.fullDisplayName} test succeeded on commit " + "${GIT_COMMIT}" + " with message \"" + env.COMMIT_MESSAGE + "\" at time ${new Date()}"
                }
                failure {
                  slackSend color: "danger", message: "The pipeline ${currentBuild.fullDisplayName} test failed on commit " + "${GIT_COMMIT}" + " with message \"" + env.COMMIT_MESSAGE + "\" at time ${new Date()}"
                }
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying....'
            }
        }
    }
}
