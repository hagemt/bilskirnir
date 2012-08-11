package edu.rpi.sdd.hagemt;

import java.util.Iterator;
import java.util.LinkedHashSet;
import java.util.Set;

/**
 * A generic Tree structure
 * @author Tor E Hagemann <hagemt@rpi.edu>
 * @param <E> the contained type
 */
public class Tree<E> extends Composite<E> {
	// Trees are hierarchies
	protected Set<Composite<E>> elements;
	
	public Tree() {
		super(null);
		elements = new LinkedHashSet<Composite<E>>();
	}
	
	private static boolean isNested(Tree<?> e1, Composite<?> e2) {
		if (e1 == e2) {
			return true;
		}
		for (Composite<?> e : e2) {
			if (isNested(e1, e)) {
				return true;
			}
		}
		return false;
	}
	
	/* Activate child capabilities */
	
	@Override
	public boolean addChild(Composite<E> e) {
		if (e.getParent() == null) {
			if (isNested(this, e)) {
				return false;
			}
			if (elements.add(e)) {
				e.setParent(this);
				return true;
			}
		}
		return false;
	}
	
	@Override
	public boolean removeChild(Composite<E> e) {
		if (elements.remove(e)) {
			e.setParent(null);
			return true;
		}
		return false;
	}

	@Override
	public Iterator<Composite<E>> iterator() {
		return elements.iterator();
	}
}
