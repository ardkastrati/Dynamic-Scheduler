package controller;

/**
 * The ParserException occurs when the file is not structured correctly.
 * 
 * @author ardkastrati
 * @version 1
 */
public class ParserException extends Exception {
    
    private static final long serialVersionUID = 1L;

    /**
     * Constructs a new ParserException class
     */
    public ParserException() {
        super();
    }

    /**
     * Constructs a new ParserException class with an argument indicating the
     * exception.
     * 
     * @param message
     *            The message indicating the problem.
     */
    public ParserException(String message) {
        super(message);
    }

    /**
     * Constructs a new ParserException class with an argument indicating the
     * cause of the exception.
     * 
     * @param cause
     *            The message indicating the cause of the problem.
     */
    public ParserException(Throwable cause) {
        super(cause);
    }

    /**
     * Constructs a new ParserException class with an argument indicating the
     * exception and the cause of the exception.
     * 
     * @param cause
     *            The message indicating the cause of the problem.
     * @param message
     *            The message indicating the problem.
     */
    public ParserException(String message, Throwable cause) {
        super(message, cause);
    }

}
