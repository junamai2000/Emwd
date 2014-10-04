<?header
#include <string>
#include <boost/lexical_cast.hpp>
#include <web/Helper.h>
#include "models/Fortune.h"
#include "views/View.h"
?>
<?init
FortuneTmplArgs *args = (FortuneTmplArgs*)stash;
?>
<!DOCTYPE html>
<html>
<head>
<title>Fortunes</title>
</head>
<body>
<table>
<tr><th>id</th><th>message</th></tr>
<?c++
Fortune::Fortunes::iterator it;
for (it = args->fortunes->begin(); it != args->fortunes->end(); ++it) {
?>
<tr>
<td>
<?=
boost::lexical_cast<std::string>((*it)->id)
?>
</td>
<td>
<?=
Emwd::web::Helper::encode((*it)->message)
?>
</td>
</tr>
<?c++
}
?>
</table>
</body>
</html>
