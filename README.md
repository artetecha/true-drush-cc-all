# True `drush cc all`

If one were to dig into [drush](https://github.com/drush-ops/drush)'s codebase, they'd find out that `drush cache-clear all` (or `drush cc all`) is not equivalent to clearing all the caches that you can see if you just type `drush cache-clear` (as I would personally expect).

For example, this is what you get on a Drupal site that has Token, Views and Varnish modules installed. 

```bash
$ drush cache-clear

Enter a number to choose which cache to clear.
 [0]   :  Cancel         
 [1]   :  all            
 [2]   :  drush          
 [3]   :  theme-registry 
 [4]   :  menu           
 [5]   :  css-js         
 [6]   :  block          
 [7]   :  module-list    
 [8]   :  theme-list     
 [9]   :  registry       
 [10]  :  token          
 [11]  :  varnish        
 [12]  :  views
```

But if one were to run `drush cache-clear all` this will not clear `token`, `varnish`, `views` or even `block`.
This is because `drush cc all` does only two things: it clears internal drush caches and it invokes `drupal_flush_all_caches()`. This is a core Drupal API that is not aware of the various implemenations of `hook_drush_cache_clear()`. 

What we provide here is a re-implemention of `all` so that it truly clears all the caches.
