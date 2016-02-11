package model.commands;

/**
 * The CommandExcpetion occurs when a command doesn't exist or it isn't used properly.
 * 
 * @author ardkastrati
 * @version 1
 */
public class CommandException extends Exception {

    private static final long serialVersionUID = 1L;

    /**
     * Constructs a new CommandException instance.
     */
    public CommandException() {
        super();
    }

    /**
     * Constructs a new CommandException instance with an argument indicating the
     * exception cause.
     * 
     * @param message The message indicating the problem.
     */
    public CommandException(String message) {
        super(message);
    }

    /**
     * Constructs a new CommandException instance with an argument indicating the
     * exception cause.
     * 
     * @param cause The message indicating the cause of the problem.
     */
    public CommandException(Throwable cause) {
        super(cause);
    }

    /**
     * Constructs a new CommandException instance with an argument indicating the
     * exception and its cause.
     * 
     * @param cause The message indicating the cause of the problem.
     * @param message The message indicating the problem.
     */
    public CommandException(String message, Throwable cause) {
        super(message, cause);
    }
}
