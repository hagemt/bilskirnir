package edu.rpi.sdd.hagemt;

/**
 * A generic composition (iteration dependent on Leaf/Tree subtype)
 * @author Tor E Hagemann <hagemt@rpi.edu>
 * @param <E> 
 */
public abstract class Composite<E> implements Iterable<Composite<E>> {
	// Maintain a parent reference
	protected Composite<E> parent;
	
	protected Composite() {
		this(null);
	}
	
	protected Composite(Composite<E> p) {
		parent = p;
	}
	
	public Composite<E> getParent() {
		return parent;
	}
	
	protected void setParent(Composite<E> e) {
		parent = e;
	}
	
	/* Shortcut methods, not entirely necessary */
	
	public final boolean addChild(E e) {
		return this.addChild(new Leaf<E>(e));
	}
	
	public final boolean removeChild(E e) {
		return this.removeChild(new Leaf<E>(e));
	}
	
	/* Provide default implementations that fail */
	
	protected boolean addChild(Composite<E> e) {
		return false;
	}
	
	protected boolean removeChild(Composite<E> e) {
		return false;
	}
}
