<?header
#include "models/Fortune.h"
?>
<?init
struct FortuneTmplArgs;
{
    std::string output;
    Fortunes fortunes;
};
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
<tr>
<?c++ for() { ?>
<td><?= fortune->id ?></td>
<td><?= fortuen->message ?></td>
<?c++ } ?>
</tr>
</table>
</body>
</html>
