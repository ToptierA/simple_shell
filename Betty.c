#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define DELIMITER " \t\r\n\a"

int main(void)
{
	    char *input;
	        char **args;
		    int status;

		        do {
				        printf("> ");
					        input = read_input();
						        args = split_input(input);
							        status = execute(args);
								        free(input);
									        free(args);
										    } while (status);

			    return 0;
}

char *read_input(void)
{
	    char *buffer = malloc(sizeof(char) * BUFFER_SIZE);
	        int position = 0;
		    int c;

		        if (!buffer) {
				        fprintf(stderr, "Allocation error\n");
					        exit(EXIT_FAILURE);
						    }

			    while (1) {
				            c = getchar();

					            if (c == EOF || c == '\n') {
							                buffer[position] = '\0';
									            return buffer;
										            } else {
												                buffer[position] = c;
														        }

						            position++;

							            if (position >= BUFFER_SIZE) {
									                fprintf(stderr, "Input too long\n");
											            exit(EXIT_FAILURE);
												            }
								        }
}

char **split_input(char *input)
{
	    char *tokens = malloc(sizeof(char) * BUFFER_SIZE);
	        char *token;
		    int position = 0;

		        if (!tokens) {
				        fprintf(stderr, "Allocation error\n");
					        exit(EXIT_FAILURE);
						    }

			    token = strtok(input, DELIMITER);

			        while (token != NULL) {
					        tokens[position] = token;
						        position++;

							        if (position >= BUFFER_SIZE) {
									            fprintf(stderr, "Too many arguments\n");
										                exit(EXIT_FAILURE);
												        }

								        token = strtok(NULL, DELIMITER);
									    }

				    tokens[position] = NULL;
				        return tokens;
}

int execute(char **args)
{
	    pid_t pid, wpid;
	        int status;

		    pid = fork();

		        if (pid == 0) {
				        if (execvp(args[0], args) == -1) {
						            perror("Error");
							            }

					        exit(EXIT_FAILURE);
						    } else if (pid < 0) {
							            perror("Error");
								        } else {
										        do {
												            wpid = waitpid(pid, &status, WUNTRACED);
													            }
