use std::collections::HashMap;
use std::hash::Hash;

use ::backtrace::Backtrace;

#[allow(unused)]
pub struct Trie<K, V>
where
    K: Eq + Hash + Clone,
    V: Clone,
{
    value: Option<V>,
    children: HashMap<K, Trie<K, V>>,
}

impl<K, V> Trie<K, V>
where
    K: Eq + Hash + Clone,
    V: Clone,
{
    #[allow(unused)]
    fn new() -> Trie<K, V> {
        Trie {
            value: None,
            children: HashMap::new(),
        }
    }

    #[allow(unused)]
    fn insert(&mut self, path: &[K], v: V) {
        if path.is_empty() {
            match self.value {
                Some(_) => {
                    let bt = Backtrace::new();
                    println!("{bt:?}");
                    panic!("key exists")
                }
                None => {
                    self.value = Some(v);
                }
            }
            return;
        }

        self.children
            .entry(path[0].clone())
            .or_insert_with(|| Trie::new())
            .insert(&path[1..], v);
    }

    #[allow(unused)]
    fn fetch(&self, path: &[K]) -> Option<V> {
        match path.len() {
            0 => self.value.clone(),
            _ => self
                .children
                .get(&path[0])
                .and_then(|child| child.fetch(&path[1..])),
            // _ => self
            //     .children
            //     .get(&path[0])
            //     .unwrap()
            //     .fetch(path[1..].to_vec()),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn fetch_works() {
        let mut t = Trie::new();
        t.insert(&[1], 3);
        let f = t.fetch(&[1]);
        assert_eq!(f, Some(3));
    }

    #[test]
    fn deep_fetch_works() {
        let mut t = Trie::new();
        t.insert(&[1, 2, 3], 4);

        let v1 = t.fetch(&[1]);
        assert_eq!(v1, None);

        let v2 = t.fetch(&[1, 2, 3]);
        assert_eq!(v2, Some(4));
    }

    #[ignore]
    #[test]
    #[should_panic]
    fn insert_panics_if_exists() {
        let mut t = Trie::new();
        t.insert(&[1], 3);
    }

    #[test]
    fn insert_works_if_none() {
        let mut t = Trie::new();
        t.insert(&[1, 2, 3], 4);
        t.insert(&[1, 2], 5);

        assert_eq!(t.fetch(&[1]), None);
        assert_eq!(t.fetch(&[1, 2]), Some(5));
        assert_eq!(t.fetch(&[1, 2, 3]), Some(4));
    }

    #[test]
    fn works_with_multiple_types() {
        let mut t = Trie::new();
        t.insert(&[1, 2, 3], "hello");
        t.insert(&[1, 3, 4], "goodbye");

        assert_eq!(t.fetch(&[1]), None);
        assert_eq!(t.fetch(&[1, 2, 3]), Some("hello"));
        assert_eq!(t.fetch(&[1, 3, 4]), Some("goodbye"));
    }

    #[test]
    fn should_return_none() {
        let mut t = Trie::new();
        t.insert(&[1, 2, 3], "hello");
        t.insert(&[1, 3, 4], "goodbye");

        assert_eq!(t.fetch(&[1]), None);
        assert_eq!(t.fetch(&[1, 2, 3]), Some("hello"));
        assert_eq!(t.fetch(&[1, 3, 4]), Some("goodbye"));
        assert_eq!(t.fetch(&[1, 4]), None);
    }
}
