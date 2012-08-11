package edu.rpi.sdd.hagemt;

import java.util.Iterator;

/**
 * A generic Leaf structure
 * @author Tor E Hagemann <hagemt@rpi.edu>
 * @param <E> the contained type
 */
public class Leaf<E> extends Composite<E> {
	// Leaf wraps a single element
	protected final E element;
	
	public Leaf(E e) {
		// No default parent
		super(null);
		element = e;
	}

	/* Iterating over a leaf is a NO-OP */
	
	@Override
	public Iterator<Composite<E>> iterator() {
		return new Iterator<Composite<E>>() {
			@Override
			public boolean hasNext() {
				return false;
			}

			@Override
			public Composite<E> next() {
				return null;
			}

			@Override
			public void remove() {
				Leaf.this.getParent().removeChild(Leaf.this);
			}
		};
	}
	
	@Override
	public String toString() {
		return element.toString();
	}
}
