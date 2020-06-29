pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                echo 'Building..'
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
                export CODECOV_TOKEN="5308a539-fd1a-4efd-9e54-6cefa3b2b6ab"
                bash <(curl -s https://codecov.io/bash)
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying....'
            }
        }
    }
}
