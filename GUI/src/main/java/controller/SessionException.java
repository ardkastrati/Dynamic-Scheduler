package controller;

/**
 * The ParserException occurs when the file is not structured correctly.
 * 
 * @author ardkastrati
 * @version 1
 */
public class SessionException extends Exception {
    
    private static final long serialVersionUID = 1L;

    /**
     * Constructs a new SessionException class
     */
    public SessionException() {
        super();
    }

    /**
     * Constructs a new SessionException class with an argument indicating the
     * exception.
     * 
     * @param message
     *            The message indicating the problem.
     */
    public SessionException(String message) {
        super(message);
    }

    /**
     * Constructs a new SessionException class with an argument indicating the
     * cause of the exception.
     * 
     * @param cause
     *            The message indicating the cause of the problem.
     */
    public SessionException(Throwable cause) {
        super(cause);
    }

    /**
     * Constructs a new SessionException class with an argument indicating the
     * exception and the cause of the exception.
     * 
     * @param cause
     *            The message indicating the cause of the problem.
     * @param message
     *            The message indicating the problem.
     */
    public SessionException(String message, Throwable cause) {
        super(message, cause);
    }

}
